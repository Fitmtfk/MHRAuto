#!/usr/bin/env python
# coding: utf-8

# In[1]:


skilllen=[" 11 11 31 31 "," 33 11 53 31 "," 55 11 75 31 "," 77 11 97 31 "," 99 11 119 31 "," 121 11 141 31 "," 143 11 162 31 "," 165 11 185 31 "," 187 11 207 31 "]


# In[2]:


train = []
f = open("d:/ocr/word.txt", encoding="utf-8")
train = f.read().split('\n')
f.close()


# In[5]:


s=""
for i in range(0,len(train)):
    for k in range(0,len(train[i])):
        s+=train[i][k]+skilllen[k]+str(i)+"\r\n"


# In[7]:


#print(s)
#box文件名需要和merge后的tif文件名相同
with open('example.box', 'w') as f:
    f.write(s)
    f.close

# In[ ]:




