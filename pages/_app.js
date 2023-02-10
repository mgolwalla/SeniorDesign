import "../styles/globals.css";

// export default function App({ Component, pageProps }) {
// var SerialPort = require("serialport");
// const parsers = SerialPort.parsers;
// const parser = new parsers.Readline({
//   delimiter: "\r\n",
// });

// var port = new SerialPort("COM3 (Arduino Uno)", {
//   baudRate: 9600,
//   dataBits: 8,
//   parity: "none",
//   stopBits: 1,
//   flowControl: false,
// });

// port.pipe(parser);
// parser.on("data", function (data) {
//   console.log(data);
// });
//   return <Component {...pageProps} />;
// }

import React from "react";

const App = ({ Component }) => {
  return (
    <div>
      <Component />
    </div>
  );
};

export default App;
