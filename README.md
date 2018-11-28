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


# Run 

`./index [kitti/voc/coco] -[i/m/t/...]`

Choose the dataset you want and the opration to do.
You need to build up dataset first.



more function is comming soon... 
[Todo] fixed point policy
[Todo] modify policy for input_data_flow
