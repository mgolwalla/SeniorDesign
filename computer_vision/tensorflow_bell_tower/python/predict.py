# The steps implemented in the object detection sample code: 
# 1. for an image of width and height being (w, h) pixels, resize image to (w', h'), where w/h = w'/h' and w' x h' = 262144
# 2. resize network input size to (w', h')
# 3. pass the image to network and do inference
# (4. if inference speed is too slow for you, try to make w' x h' smaller, which is defined with DEFAULT_INPUT_SIZE (in object_detection.py or ObjectDetection.cs))
import sys
from tflite_runtime.interpreter import Interpreter
import numpy as np
from object_detection import ObjectDetection
import cv2
from picamera2 import Picamera2
from tflite_runtime.interpreter import Interpreter 
import numpy as np
from PIL import Image
import time
import serial

MODEL_FILENAME = 'model.tflite'
LABELS_FILENAME = 'labels.txt'


class TFLiteObjectDetection(ObjectDetection):
    """Object Detection class for TensorFlow Lite"""
    def __init__(self, model_filename, labels):
        super(TFLiteObjectDetection, self).__init__(labels)
        self.interpreter = Interpreter(model_path=model_filename)
        self.interpreter.allocate_tensors()
        self.input_index = self.interpreter.get_input_details()[0]['index']
        self.output_index = self.interpreter.get_output_details()[0]['index']

    def predict(self, preprocessed_image):
        inputs = np.array(preprocessed_image, dtype=np.float32)[np.newaxis, :, :, (2, 1, 0)]  # RGB -> BGR and add 1 dimension.

        # Resize input tensor and re-allocate the tensors.
        self.interpreter.resize_tensor_input(self.input_index, inputs.shape)
        self.interpreter.allocate_tensors()

        self.interpreter.set_tensor(self.input_index, inputs)
        self.interpreter.invoke()
        return self.interpreter.get_tensor(self.output_index)[0]


def main():
    cv2.startWindowThread()

    ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
    ser.flush()

    picam2 = Picamera2()
    picam2.configure(picam2.create_preview_configuration(main={"format": 'XRGB8888', "size": (416, 416)}))
    picam2.start()
    # Load labels
    with open(LABELS_FILENAME, 'r') as f:
        labels = [label.strip() for label in f.readlines()]

    od_model = TFLiteObjectDetection(MODEL_FILENAME, labels)

    while True:
        time.sleep(0.1)
        img = picam2.capture_array()
        img = cv2.cvtColor(img, cv2.COLOR_RGBA2RGB)
        img = Image.fromarray(img)
        predictions = od_model.predict_image(img)
        
        open_cv_image = np.array(img)
        side = open_cv_image.shape[0]
        for prediction in predictions:
            if prediction['probability'] > 0.6:
                x = prediction['boundingBox']['left']
                y = prediction['boundingBox']['top']
                w = prediction['boundingBox']['width']
                h = prediction['boundingBox']['height']
                cv2.rectangle(open_cv_image, (int(x * side),int(y * side)), (int(x * side)+int(w * side), int(y * side)+int(h* side)), (255,0,0), 4)
                ser.write(b"blue\n")
        cv2.imshow("Output",open_cv_image)
        cv2.waitKey(1)


if __name__ == '__main__':
    main()
