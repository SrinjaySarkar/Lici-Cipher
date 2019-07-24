# import torch
# import os
# import numpy as np
# import cv2
# import matplotlib.pyplot as plt
# import torchvision.datasets as dset
# import matplotlib.pyplot as plt
# root="./mnist"
# if not os.path.exists(root):
# 	os.mkdir(root)
# # train_set=dset.MNIST(root=root,train=True,download=True)
# # test_set=dset.MNIST(root=root,train=False,download=True)

# #print(train_set)
# #print(test_set.shape)
# # bs=8
# # train_loader=torch.utils.data.DataLoader(dataset=train_set,batch_size=bs,shuffle=False)
# # test_loader=torch.utils.data.DataLoader(dataset=test_set,batch_size=bs)

# train_images_path="./MNIST_PNG/mnist_png/training"
# test_images_path="./MNIST_PNG/mnist_png/testing"
# part1_path="./part3"

# # train_paths=[]
# # for path,subdirs,files in os.walk(train_images_path):
# # 	for name in files:
# # 		train_paths.append(os.path.join(path,name))

# #print(train_paths)
# # height=width=512
# # # images_array=np.empty((5,height,width),dtype=np.float32)
# # # train_labels=np.empty(5,dtype=np.float32)
# # for i,j in enumerate(train_paths):
# # 	image=cv2.imread(j,0).astype(np.float32)
# # 	image=cv2.resize(image,dsize=(height,width))
# # 	id=j.split("/")[-2]
# # 	write_path="."+j.split(".")[1]+str("_resized")+str(".png")
# # 	if not os.path.exists(write_path):
# # 		cv2.imwrite(write_path,image)
# # 	else:
# # 		print("Passed")
# # 		pass

# # counter=0
# # for paths,subdirs,files in os.walk((train_images_path)):
# # 	for name in files:
# # 		p=os.path.join(paths,name)
# # 		#print(p)
# # 		if p.endswith("_resized.png") == False:
# # 			os.remove(p)
# # 			counter+=1
# # 			print(p)
# # print(counter)

# # images_list=[]
# # for i,j in enumerate(train_paths[:16]):
# # 	image=cv2.imread(j,0).astype(np.float32)
# # 	image/=255
# # 	images_list.append(image)

# sample_paths=[]
# for path,subdirs,files in os.walk(part1_path):
# 	for name in files:
# 			sample_paths.append(os.path.join(path,name))

# print(sample_paths)

# # print(len(images_list))
# # plt.imshow(images_list[1],cmap='gray')
# # plt.show()
import torch
from torchvision import transforms,datasets,models
model=models.resnet50(pretrained=True)
#print(model.bn1.weight)

res50_conv = torch.nn.Sequential(*list(models.resnet50(pretrained=True).children())[:-2])
#x=res50_conv.conv1.weight.shape
# print(model.bn1.weight)
# print(x)
# print(res50_conv)

for modules in res50_conv.modules():
	print(modules)
# for params in model.parameters():
# 	print(params)
