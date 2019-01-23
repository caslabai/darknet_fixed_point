#!/bin/bash

find_new_fixed1=0
#export RESTORE_BINARY_POINT=fixed_inet.conf
export RESTORE_BINARY_POINT=qvalue/fixed_Qvalue_yolov3tiny_kitti,Q4_4.fixed

#qvalue/fixed_Qvalue_yolov3tiny_kitti,QoriginalDYN.fixed

#qvalue/fixed_Qvalue_yolov3tiny_kitti,Q5_8.fixed
#qvalue/fixed_Qvalue_yolov3tiny_kitti,Ki_1,Kf_1,af_0.25.fixed
#fixed_kitti.conf
#qvalue/fixed_Qvalue_alexnet,Ki_3,Kf_1,af_0.25.fixed
#qvalue/fixed_Qvalue,Ki_3,Kf_1,af_0.5.fixed
export STORE_BINARY_POINT=qvalue/fixed_Qvalue_yolov3tiny_cooc,Ki_1,Kf_1,af_0.75.fixed
#fixed_inet_2.conf


pre_weight=./train/yolov3-tiny-voc/yolov3-tiny-voc_88600.weights
#pre_weight=weights/yolov3-tiny.conv.15


export FIXED_PLOICY_ADJUST=0



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
        voc_small)   
            cfg=./cfg/yolov3-tiny-voc.cfg
            weight=./weights/train/yolov3-tiny-voc_final.weights
            data=./cfg/voc_small.data
            ;;



        #------coco------
        coco)   
            #cfg=./cfg/yolov3.cfg
            #weight=./weights/yolov3.weights
            cfg=./cfg/yolov3-tiny.cfg
            weight=./weights/yolov3-tiny.weights
            data=./cfg/coco.data
        ;;

        coco_small)   
            #cfg=./cfg/yolov3.cfg
            #weight=./weights/yolov3.weights
            cfg=./cfg/yolov3-tiny.cfg
            weight=./weights/yolov3-tiny.weights
            data=./cfg/coco_small.data
        ;;

        #------imagenet------
        imagenet)
            cfg=./cfg/alexnet.cfg
            weight=./weights/alexnet.weights
            data=./cfg/imagenet1k.data
        ;;
        imagenet_small)
            cfg=./cfg/alexnet.cfg
            weight=./weights/alexnet.weights
            data=./cfg/imagenet1k_small.data
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

while getopts "tmicarvb"  OPTION
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
            #echo "./darknet detector test $data  $cfg  $weight  data/cars_kitti.png -ext_output -thresh 0.2"
            #./darknet detector test $data  $cfg  $weight  data/cars_kitti.png -ext_output -thresh 0.2
            ;;
        c)
            keeplayers=15
            new_name=./weights/yolov3-tiny.conv.$keeplayers
            ./darknet partial  $cfg $weight $new_name $keeplayers
            ;;
        a)
            ./darknet detector calc_anchors $data -num_of_clusters 9 -width 416 -height 416
            ;;
    
        r)
            #gdb -arg ./darknet classifier predict $data $cfg $weight data/eagle.jpg
            ./darknet classifier predict $data $cfg $weight data/dog.jpg
        ;;

        v)#find new fixed point
            #export FIND_NEW_FIXED=$find_new_fixed1
            #make clean
            #make -j40 FIND_POINT="$find_new_fixed1"
            #./darknet detector map $data $cfg $weight
            ./darknet classifier valid $data $cfg  $weight
            ;;

        b)
            make clean
            make -j40  FIND_POINT="$find_new_fixed1"
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


