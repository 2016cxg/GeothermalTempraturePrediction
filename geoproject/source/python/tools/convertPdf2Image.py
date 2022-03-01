from pdf2image import convert_from_path


pth1 = r'D:\workplace\geoproject\pictureproject\data\material\地震地层深度图\deepth.pdf'
pth2 = r'D:\workplace\geoproject\pictureproject\data\deepth\pic\poppler-0.68.0\bin'
pth3 = r'D:\workplace\geoproject\pictureproject\data\deepth\pic\\'
images = convert_from_path(pth1, 500,poppler_path=pth2)
for i, image in enumerate(images):
    fname = pth3+str(i)+'.png'
    image.save(fname, "PNG")