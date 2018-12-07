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

##imagenet
    download at: https://www.zybuluo.com/nrailgun/note/488084
    follow by : https://pjreddie.com/darknet/imagenet/


#Model
    Default with yolov3-tiny or yolov3
    you can get more yolo model at https://pjreddie.com/darknet/yolo/
    get model for image classify at https://pjreddie.com/darknet/imagenet

<table id="compare">

  <thead>
      <tr><th style="text-align:left;" role="columnheader">Model</th>
          <th style="text-align:right;" role="columnheader">Top-1</th> 
              <th style="text-align:right;" role="columnheader">Top-5</th>
                  <th style="text-align:right;" role="columnheader">Ops</th>
                      <th style="text-align:right; " role="columnheader">GPU</th>
                          <th style="text-align:right; " role="columnheader">CPU</th>
                              <th style="text-align:right; " role="columnheader">Cfg</th>
                                  <th style="text-align:right; " role="columnheader">Weights</th>
                                    </tr></thead>

                                     <tbody><tr>
                                     <td><a href="#alexnet">AlexNet</a></td>
                                     <td>57.0</td> 
                                     <td>80.3</td>
                                     <td>2.27 Bn</td>
                                     <td>3.1 ms</td>
                                     <td>0.29 s</td>
                                     <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/alexnet.cfg">cfg</a></td>
                                     <td><a href="https://pjreddie.com/media/files/alexnet.weights">238 MB</a></td>
                                     </tr>

                                      <tr>
                                      <td><a href="#reference">Darknet Reference</a></td>
                                      <td>61.1</td> 
                                      <td>83.0</td>
                                      <td style="font-weight:bold;">0.96 Bn</td>
                                      <td style="font-weight:bold;">2.9 ms</td>
                                      <td style="font-weight:bold;">0.14 s</td>
                                      <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/darknet.cfg">cfg</a></td>
                                      <td><a href="https://pjreddie.com/media/files/darknet.weights">28 MB</a></td>
                                      </tr>

                                       <tr>
                                       <td><a href="#vgg">VGG-16</a></td>
                                       <td>70.5</td> 
                                       <td>90.0</td>
                                       <td>30.94 Bn</td>
                                       <td>9.4 ms</td>
                                       <td>4.36 s</td>
                                       <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/vgg-16.cfg">cfg</a></td>
                                       <td><a href="https://pjreddie.com/media/files/vgg-16.weights">528 MB</a></td>
                                       </tr>

                                        <tr>
                                        <td><a href="#extraction">Extraction</a></td>
                                        <td>72.5</td> 
                                        <td>90.8</td>
                                        <td>8.52 Bn</td>
                                        <td>4.8 ms</td>
                                        <td>0.97 s</td>
                                        <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/extraction.cfg">cfg</a></td>
                                        <td><a href="https://pjreddie.com/media/files/extraction.weights">90 MB</a></td>
                                        </tr>

                                         <tr>
                                         <td><a href="#darknet19">Darknet19</a></td>
                                         <td>72.9</td> 
                                         <td>91.2</td>
                                         <td>7.29 Bn</td>
                                         <td>6.2 ms</td>
                                         <td>0.87 s</td>
                                         <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/darknet19.cfg">cfg</a></td>
                                         <td><a href="https://pjreddie.com/media/files/darknet19.weights">80 MB</a></td>
                                         </tr>

                                          <tr>
                                          <td><a href="#darknet19_448">Darknet19 448x448</a></td>
                                          <td>76.4</td> 
                                          <td>93.5</td>
                                          <td>22.33 Bn</td>
                                          <td>11.0 ms</td>
                                          <td>2.96 s</td>
                                          <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/darknet19_448.cfg">cfg</a></td>
                                          <td><a href="https://pjreddie.com/media/files/darknet19_448.weights">80 MB</a></td>
                                          </tr>

                                           <tr>
                                           <td><a href="#resnet18">Resnet 18</a></td>
                                           <td>70.7</td> 
                                           <td>89.9</td>
                                           <td>4.69 Bn</td>
                                           <td>4.6 ms</td>
                                           <td>0.57 s</td>
                                           <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnet18.cfg">cfg</a></td>
                                           <td><a href="https://pjreddie.com/media/files/resnet18.weights">44 MB</a></td>
                                           </tr>

                                            <tr>
                                            <td><a href="#resnet34">Resnet 34</a></td>
                                            <td>72.4</td> 
                                            <td>91.1</td>
                                            <td>9.52 Bn</td>
                                            <td>7.1 ms</td>
                                            <td>1.11 s</td>
                                            <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnet34.cfg">cfg</a></td>
                                            <td><a href="https://pjreddie.com/media/files/resnet34.weights">83 MB</a></td>
                                            </tr>

                                             <tr>
                                             <td><a href="#resnet50">Resnet 50</a></td>
                                             <td>75.8</td> 
                                             <td>92.9</td>
                                             <td>9.74 Bn</td>
                                             <td>11.4 ms</td>
                                             <td>1.13 s</td>
                                             <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnet50.cfg">cfg</a></td>
                                             <td><a href="https://pjreddie.com/media/files/resnet50.weights">87 MB</a></td>
                                             </tr>


                                              <tr>
                                              <td><a href="#resnet101">Resnet 101</a></td>
                                              <td>77.1</td> 
                                              <td>93.7</td>
                                              <td>19.70 Bn</td>
                                              <td>20.0 ms</td>
                                              <td>2.23 s</td>
                                              <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnet101.cfg">cfg</a></td>
                                              <td><a href="https://pjreddie.com/media/files/resnet101.weights">160 MB</a></td>
                                              </tr>

                                               <tr>
                                               <td><a href="#resnet152">Resnet 152</a></td>
                                               <td>77.6</td> 
                                               <td>93.8</td>
                                               <td>29.39 Bn</td>
                                               <td>28.6 ms</td>
                                               <td>3.31 s</td>
                                               <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnet152.cfg">cfg</a></td>
                                               <td><a href="https://pjreddie.com/media/files/resnet152.weights">220 MB</a></td>
                                               </tr>

                                                <tr>
                                                <td><a href="#resnext50">ResNeXt 50</a></td>
                                                <td>77.8</td> 
                                                <td>94.2</td>
                                                <td>10.11 Bn</td>
                                                <td>24.2 ms</td>
                                                <td>1.20 s</td>
                                                <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnext50.cfg">cfg</a></td>
                                                <td><a href="https://pjreddie.com/media/files/resnext50.weights">220 MB</a></td>
                                                </tr>

                                                 <tr>
                                                 <td><a href="#resnext101">ResNeXt 101 (32x4d)</a></td>
                                                 <td>77.7</td> 
                                                 <td>94.1</td>
                                                 <td>18.92 Bn</td>
                                                 <td>58.7 ms</td>
                                                 <td>2.24 s</td>
                                                 <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnext101-32x4d.cfg">cfg</a></td>
                                                 <td><a href="https://pjreddie.com/media/files/resnext101-32x4d.weights">159 MB</a></td>
                                                 </tr>

                                                  <tr>
                                                  <td><a href="#resnext152">ResNeXt 152 (32x4d)</a></td>
                                                  <td>77.6</td> 
                                                  <td>94.1</td>
                                                  <td>28.20 Bn</td>
                                                  <td>73.8 ms</td>
                                                  <td>3.31 s</td>
                                                  <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/resnext152-32x4d.cfg">cfg</a></td>
                                                  <td><a href="https://pjreddie.com/media/files/resnext152-32x4d.weights">217 MB</a></td>
                                                  </tr>

                                                   <tr>
                                                   <td><a href="#densenet201">Densenet 201</a></td>
                                                   <td>77.0</td> 
                                                   <td>93.7</td>
                                                   <td>10.85 Bn</td>
                                                   <td>32.6 ms</td>
                                                   <td>1.38 s</td>
                                                   <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/densenet201.cfg">cfg</a></td>
                                                   <td><a href="https://pjreddie.com/media/files/densenet201.weights">66 MB</a></td>
                                                   </tr>

                                                   <tr>
                                                   <td><a href="#darknet53">Darknet53</a></td>
                                                   <td>77.2</td> 
                                                   <td>93.8</td>
                                                   <td>18.57 Bn</td>
                                                   <td>13.7 ms</td>
                                                   <td>2.11 s</td>
                                                   <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/darknet53.cfg">cfg</a></td>
                                                   <td><a href="https://pjreddie.com/media/files/darknet53.weights">159 MB</a></td>
                                                   </tr>

                                                   <tr>
                                                   <td><a href="#darknet53_448">Darknet53 448x448</a></td>
                                                   <td style="font-weight:bold;">78.5</td> 
                                                   <td style="font-weight:bold;">94.7</td>
                                                   <td>56.87 Bn</td>
                                                   <td>26.3 ms</td>
                                                   <td>7.21 s</td>
                                                   <td><a href="https://github.com/pjreddie/darknet/blob/master/cfg/darknet53_448.cfg">cfg</a></td>
                                                   <td><a href="https://pjreddie.com/media/files/darknet53_448.weights">159 MB</a></td>
                                                   </tr>
                                                   </tbody></table>





# Training

    how to train your own model... 
    [Todo] make doc.


# Genarate fixed point config

We need to decide fractional point for each layer by some data. <br>
Set `FIND_POINT & GEMM_FIXED & BIAS_FIXED =1` in Makefile and `make -j40`<br>
Run `./index kitti_small -m #run 20 image for decide fractional point `<br>
Set `FIND_POINT=0 ` in Makefile and `make -j40`<br>
Run project with fixed point config file. <br>


# Run 

Run yolov3-tiny for different config
`./index [kitti/voc/coco] -[?/i/m/t/...]`

Choose the dataset you want and the opration to do.
You need to build up dataset first.









more function is comming soon... 
[Todo] fixed point policy
[Todo] modify policy for input_data_flow
