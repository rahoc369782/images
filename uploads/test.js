const express = require("express");
const http = require("http");
const NodeMediaServer = require("node-media-server");
const app = express();
const server = http.createServer(app);
const io = require("socket.io")(server);

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/test.html");
});

const config = {
  rtmp: {
    port: 1935,
    chunk_size: 60000,
    gop_cache: true,
    ping: 30,
    ping_timeout: 60,
  },
  http: {
    port: 8000,
    allow_origin: "*",
  },
  // Add your logging configuration here
  logType: 3, // Use the appropriate log type based on your needs
};

const nms = new NodeMediaServer(config);

nms.run();

io.on("connection", (socket) => {
  console.log("a user connected");

  socket.on("msg", (data) => {
    console.log(data);
  });

  socket.on("stream", (image) => {
    console.log(image);
    // Broadcast the image to all other clients
    socket.broadcast.emit("stream", image);
  });
});

server.listen(8080, () => {
  console.log("Server is running on port 8080");
});
