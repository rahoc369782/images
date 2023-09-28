const express = require("express");
const multer = require("multer");
const path = require("path");
const app = express();
const port = process.env.PORT || 3000;

// Define the storage for uploaded images
const storage = multer.diskStorage({
  destination: "./uploads/", // Set your upload directory path here
  filename: function (req, file, cb) {
    cb(
      null,
      file.fieldname + "-" + Date.now() + path.extname(file.originalname)
    );
  },
});

// Initialize multer for handling file uploads
const upload = multer({ storage });

// Serve static files (uploaded images)
app.use("/uploads", express.static("uploads"));

// Define a route for image uploads
app.post("/upload", upload.array("files"), (req, res) => {
  if (!req.files) {
    return res.status(400).send("No file uploaded.");
  }
  res.status(200).send(req.files);
});

// Start the server
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
