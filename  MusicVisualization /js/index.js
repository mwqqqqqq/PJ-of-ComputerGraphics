window.onload = function (){
    var file = document.getElementById("musicfile");
    var audio = document.getElementById("audio");

    file.onchange = function(){
        var canvas = document.getElementById("canvas");
        var ctx = canvas.getContext("2d");
        //var img1=new Image()  //可视化焦点图
        //img1.src="timg1.jpg"
        var img2=new Image()  //背景图
        img2.src="timg.jpg"
        var files = this.files;
        
        canvas.width  = window.innerWidth;
        center_width =canvas.width/2;
        canvas.height = window.innerHeight;
        center_height =canvas.height/2;
        
        //2.播放进度条
        audio.src = URL.createObjectURL(files[0]);
        audio.load();
        audio.play();
        //3.解析音乐文件
        var context = new (window.AudioContext || window.webkitAudioContext)();
        var src = context.createMediaElementSource(audio);
        var analyser = context.createAnalyser();
        src.connect(analyser);
        analyser.connect(context.destination);
        var bufferLength = analyser.frequencyBinCount*44100/context.sampleRate|0;
        var dataArray = new Uint8Array(bufferLength);
        

        function frameLooper() {
            //1.绘制背景图
            ctx.drawImage(img2,0,0, canvas.width, canvas.height);//加载背景图
            ctx.fillStyle = "rgba(255, 255, 255, " + (0 * 0.0000125 - 0.4) + ")";
            ctx.fillRect(0, 0, canvas.width, canvas.height);

             intensity = 0;
                analyser.getByteFrequencyData(dataArray);//获取频域数据
                //画线条
                for (var i = 0; i < 180; i++) {
                    var value = dataArray[i+180] / 8;
                    intensity += value*3;
                    ctx.beginPath();
                    ctx.lineWidth = 2;
                    ctx.moveTo(center_width, center_height);
                    //R * cos (PI/180*一次旋转的角度数) ,-R * sin (PI/180*一次旋转的角度数)
                    ctx.lineTo(Math.cos((i * 2) / 180 * Math.PI) * (200 + value*3) + center_width, (- Math.sin((i * 2) / 180 * Math.PI) * (200 + value * 3) + center_height));
                    //var temp_x = Math.cos((i * 1) / 180 * Math.PI) * (200 + value * 2) + center_width;
                    //var temp_y =(- Math.sin((i * 1) / 180 * Math.PI) * (200 + value) + center_height);
                    ctx.stroke();
                }
                //画一个小圆，将线条覆盖
                
                ctx.beginPath();
                ctx.lineWidth = 1;
                ctx.arc(center_width, center_height, 200+intensity*0.005, 0, 2 * Math.PI, false);
                //ctx.drawImage(img1,center_width, center_height, 200,200);
                ctx.fillStyle = "#CDC9A5";
                //ctx.fillStyle = "rgba(255, 255, 255, " + (0 * 0.0000125 - 0.4) + ")";
                //ctx.fillRect(0, 0, center_width, center_height);
                ctx.stroke();
                ctx.fill();
                                            
                analyser.getByteTimeDomainData(dataArray);
                var height = 200, width = 300;
                ctx.beginPath();
                for (var i = 0; i < width; i++) {
                ctx.lineTo(i + center_width-150, center_height - (height / 2 * (dataArray[dataArray.length * i / width | 0] / 256 - 0.5)));
                }
                ctx.stroke();
                requestAnimationFrame(frameLooper);
        }//framlooper

        audio.play();
        frameLooper();
    };//onchange

};//onload
