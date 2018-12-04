#!/bin/bash

#cfg=''
#weight=''
#data=''

pre_weight=./train/yolov3-tiny-voc/yolov3-tiny-voc_88600.weights
#pre_weight=weights/yolov3-tiny.conv.15




#====================================================
#                     dataset 
#====================================================

get_data(){    
    case $1 in
        
        #------kitti------
        kitti)  
            cfg=./cfg/yolov3-tiny-kitti.cfg
            weight=./weights/train/yolov3-tiny-kitti_f_tmp.weights
            data=./cfg/kitti.data
            ;;
        kitti_small)  
            cfg=./cfg/yolov3-tiny-kitti.cfg
            weight=./weights/train/yolov3-tiny-kitti_f_tmp.weights
            data=./cfg/kitti_small.data
            ;;
    
        #------voc------
        voc)   
            cfg=./cfg/yolov3-tiny-voc.cfg
            weight=./weights/train/yolov3-tiny-voc_final.weights
            data=./cfg/voc.data
            ;;
    
        #------coco------
        coco)   
            #cfg=./cfg/yolov3.cfg
            #weight=./weights/yolov3.weights
            cfg=./cfg/yolov3-tiny.cfg
            weight=./weights/yolov3-tiny.weights
            data=./cfg/coco.data
        ;;
    esac
}

#====================================================
#                    help 
#====================================================
usage()
{
   echo "usage: ./index  \$dataset_name(kitti,voc,coco  -[t/m/i/...])"
             #echo " Help menu" 
            echo -e " \n--------------------\nFlags:" 
            echo -e " -t\ttrain" 
            echo -e " -m\tmAP" 
            echo -e " -i\t inference. Run yolo v3:" 
            echo -e " -i\t cut weight:" 
            echo -e " -a\t recalculate anchor:" 
}



#====================================================
#                    main 
#====================================================

get_data $1 
shift

while getopts "tmica"  OPTION
do
    case $OPTION in
        t)
            
            ./darknet detector train $data  $cfg $pre_weight -dont_show -gpus 0
            ;;
        m)
            ./darknet detector map $data  $cfg $weight 
            ;;
        i)
            ./darknet detector test $data  $cfg  $weight  data/bus.jpg -ext_output -thresh 0.2
            ;;
        c)
            keeplayers=15
            new_name=./weights/yolov3-tiny.conv.$keeplayers
            ./darknet partial  $cfg $weight $new_name $keeplayers
            ;;
        a)
            ./darknet detector calc_anchors $data -num_of_clusters 9 -width 416 -height 416
            ;;
    
        \?)
            exit 0
            ;;
    esac
done

#-iou_thresh 0.1 




: '
while [ "$1" != "" ]; do
    case $1 in
        -i | --inference )           shift
                                dataset_name=$1
                                get_data $dataset_name
                                ;;
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done
'


