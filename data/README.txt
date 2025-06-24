This folder is used to store dataset files for the KNN digit recognition project.

It contains:

- mnist/              → The original MNIST dataset (images and labels in IDX format)
- custom_dataset/     → The user-generated digit dataset created using the CustomDigitDataset project
  ├── images/         → Binary file containing 28x28 grayscale images (images.bin)
  └── labels/         → Corresponding digit labels (labels.bin)

⚠️ Notes:
- The MNIST files must be downloaded separately from: http://yann.lecun.com/exdb/mnist/
- The custom dataset is created by running the CustomDigitDataset tool.

📦 Custom Dataset Tool:
You can find the CustomDigitDataset project here:
https://github.com/UnaizaAsif/CustomDigitDataset

These datasets are loaded by the program at runtime for training and classification.
