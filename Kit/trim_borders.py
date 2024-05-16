import os
from PIL import Image, ImageChops

# Name of outputted image
output_folder = "cropped_images"

def remove_black_border(im):
    # Thanks to https://stackoverflow.com/questions/19271692/removing-borders-from-an-image-in-python
    # for the original code
    bg = Image.new(im.mode, im.size, im.getpixel((0,0)))
    diff = ImageChops.difference(im, bg)
    diff = ImageChops.add(diff, diff, 2.0, -100)
    bbox = diff.getbbox()
    if bbox:
        return im.crop(bbox)

# Check if output folder exists, if not, create it
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# Process each JPG image in the current directory
for filename in os.listdir("."):
    if filename.endswith((".jpg", ".png", ".jpeg")):
        input_image = Image.open(filename)
        cropped_image = remove_black_border(input_image)
        if cropped_image:
            cropped_image.save(os.path.join(output_folder, filename))
            print("Cropped", filename, "and saved to", os.path.join(output_folder, filename))
        else:
            print("No black border detected in", filename)
