This repo is focus on yolov3-tiny

After enable fixed point calculation in Makefile (fixed point only support on CPU, pls set `GPU=0` ) <br>
You can setup frational point in `fixed.h`. 

(only simulate the value range to fixed-point still calculate with float on cpu)



# Dataset

    explain how to build up dataset

## coco

    As here https://pjreddie.com/darknet/yolo/

## voc

    As here https://pjreddie.com/darknet/yolo/


## kitti

    convert by custem code
    updating... 
    [Todo] collecting convertion code & make doc.

# Training

    how to train your own model... 
    [Todo] make doc.


# Genarate fixed point config

We need to decide fractional point for each layer by some data.
Set `FIND_POINT & GEMM_FIXED & BIAS_FIXED =1` in Makefile and `make -j40`
Run `./index kitti_small -m #run 20 image for decide fractional point `
Set `FIND_POINT=0 ` in Makefile and `make -j40`
Run project with fixed point config file. 


# Run 

`./index [kitti/voc/coco] -[?/i/m/t/...]`

Choose the dataset you want and the opration to do.
You need to build up dataset first.







more function is comming soon... 
[Todo] fixed point policy
[Todo] modify policy for input_data_flow
