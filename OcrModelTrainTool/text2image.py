#!/usr/bin/env python
# coding: utf-8

# In[1]:


from PIL import Image,ImageFont,ImageDraw
import os
from PIL import Image,ImageFont,ImageDraw


# In[2]:


def t2p(text):
    im = Image.new("RGB", (220, 40), (255, 255, 255))
    dr = ImageDraw.Draw(im)
    font = ImageFont.truetype("d:/ocr/MYingHeiPRC-W5.ttf", 22)
    dr.text((10, 5), text, font=font, fill="#000000")
    #im.show()
    im.save("d:/ocr/image/"+text+".png")


# In[3]:


train = []
f = open("d:/ocr/word.txt", encoding="utf-8")
train = f.read().split('\n')
f.close()


# In[4]:


for i in train:
    t2p(i)




