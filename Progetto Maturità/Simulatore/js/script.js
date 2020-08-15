var tratte=new Array();

$(function(){
    $("#linee").load( "http://bustracker.altervista.org/Simulatore/lineeHtml.php" );
    
    $("#btnStart").click(function(){
        $("#linee input:checked").each(function(){
            var tds=$(this).parent().parent().parent().children();
            
            var trattaObj=new Object();
            trattaObj.linea=$(tds).eq(2).text();
            trattaObj.id=$(tds).eq(1).text();
            trattaObj.orario=$(tds).eq(3).children().eq(0).val();
            trattaObj.orariotxt=$(tds).eq(3).children().eq(0).find('option:selected').text();;
            trattaObj.ritardo=$(tds).eq(4).children().eq(0).val();
            trattaObj.autista =$(tds).eq(5).children().eq(0).val();
            trattaObj.autistatxt=$(tds).eq(5).children().eq(0).find('option:selected').text();;
            trattaObj.autobus=$(tds).eq(6).children().eq(0).val();
            trattaObj.autobustxt=$(tds).eq(6).children().eq(0).find('option:selected').text();;
            trattaObj.nomeFile=$(tds).eq(7).children().eq(0).val();
            trattaObj.row=$(this).parent().parent().parent().html();
            trattaObj.stopped=false;
            var supp=$(this);
            
            $(this).attr("checked",false);
           
            if( trattaObj.nomeFile!=""){
                
                $.get( "http://bustracker.altervista.org/Simulatore/getFile.php?file_name="+trattaObj.nomeFile, function( data ) {
                    trattaObj.thread=true;
                    tratte.push(trattaObj);  
                    $(supp).parent().parent().parent().remove();
                    
                    $("#tratte").append('<tr>'+
                            "<td><label class='checkbox-inline'><input type='checkbox' >Seleziona</label></td>"+
                            '<td><span>'+trattaObj.id+'</span></td>'+
                            '<td><span>'+trattaObj.linea+'</span></td>'+
                            '<td><span>'+trattaObj.orariotxt+'</span></td>'+
                            '<td>'+
                            '     <span>'+trattaObj.ritardo+' min.</span>'+
                            '</td>'+
                            '<td>'+
                            '   <span>'+trattaObj.autistatxt+'</span>'+
                            '</td>'+
                            '<td>'+
                            '    <span>'+trattaObj.autobustxt+'</span>'+
                            '</td>'+
                            '<td>'+
                                trattaObj.nomeFile+
                            '</td>'+
                        '</tr>');
                     $("#tratte").append("<tr>"+
                        "<td colspan='8'>"+
                            "<div class='progress'>"+
                            "<div class='progress-bar'id='"+trattaObj.orario+"_progress' role='progressbar' aria-valuenow='0'"+
                            "aria-valuemin='0' aria-valuemax='100' style='width:0%'>"+
                            "<span class='sr-only'></span>"+
                            "</div>"+
                            "</div>"+
                        "</td>"+
                    "</tr>");
                    
                    var progressbar=$("#"+trattaObj.orario+"_progress");
                    
                    //CREA TRATTA
                    var params;
                    params = new FormData();
                    params.append( 'IDAutobus', trattaObj.autobus);
                    params.append( 'IDAutista', trattaObj.autista);
                    params.append( 'IDOrario', trattaObj.orario);
                    params.append( 'Ritardo', trattaObj.ritardo);
                   $.ajax({
                    type: 'POST',
                    url: "http://bustracker.altervista.org/Simulatore/CreaTratta.php",
                    data: params,
                    processData: false,
                    contentType: false,
                    dataType:"html",
                    async:false
                    }).done(function(data){
                        trattaObj.idTratta=data;
                    });
                    /////////////////////////////////////////
                   
                    var dataArray = data.split("\n");
                    var totalTime=0;
                    for(var i=0;i< dataArray.length;i++){
                        if(dataArray[i]!=""){
                        var row=dataArray[i].split(";");
                        totalTime+=parseInt(row[2]);
                        }
                    }
                    var factor = 100/totalTime;
                    StartSimulating(dataArray,0,0,progressbar,factor,trattaObj,0);
                    
                    
                    
                    
                 });
                    
            }else
                $(this).attr("checked",false);
        });
    });
    
    function StartSimulating(data,i,curtime,progressbar,factor,trattaObj,count){
        if(trattaObj.stopped==false && trattaObj!=undefined){
	    
            var row=data[i].split(";");
            
            //INVIA COORDINATE
            var pos;
            pos = new FormData();
            pos.append( 'IDTratta', trattaObj.idTratta);
            pos.append( 'Offset', curtime);
            pos.append( 'Lat',row[0]);
            pos.append( 'Lon', row[1]);
	    if(count==10)
	    {
		pos.append('notification',"OK");
		count=0;
	    }
            $.ajax({
            type: 'POST',
            url: "http://bustracker.altervista.org/Simulatore/AddTappa.php",
            data: pos,
            processData: false,
            contentType: false,
            dataType:"html",
            async:true,
	success:function(result){
		console.log(result);
	}
            });
            count++;
            //////////////////
            var wait=parseInt(row[2])
            curtime+=wait;
            var speed=parseInt($("#speed").val());
            if(!isNaN(speed) && speed>0)
                 wait=wait/speed;
            
            $(progressbar).attr("aria-valuenow",Math.round(factor*curtime));
            $(progressbar).attr("style","width:"+Math.round(factor*curtime)+"%");
            i++;
            if(i< data.length)
                setTimeout(StartSimulating,wait,data,i,curtime,progressbar,factor,trattaObj,count);
            else
            {
               $.each(tratte, function(i){
                if(tratte[i] === trattaObj) {
                    tratte.splice(i,1);
                    return false;
                }
               });
                $("#tratte tr").each(function(index,value){
                    if(index % 2==0)
                    {
                        if($(this).children().eq(1).children().eq(0).text()==trattaObj.id)
                        {
                            $(this).parent().children().eq(index+1).remove();
                            $(this).remove();
							//stoppa tratta sul DB
                            var params;
                            params = new FormData();
                            params.append( 'IDTratta', trattaObj.idTratta);
                            $.ajax({
                                type: 'POST',
                                url: "http://bustracker.altervista.org/Simulatore/StopTratta.php",
                                data: params,
                                processData: false,
                                contentType: false,
                                dataType:"html",
                                async:false
                            });
                            ///////////////////////
                            $("#linee").append("<tr>"+trattaObj.row+"<tr/>");
                        }
                    }
                });
            }
        }
    }
    

    $("#btnStop").click(function(){
        $("#tratte input:checked").each(function(){
            var tds=$(this).parent().parent().parent().children();
            var id=$(tds).eq(1).text();
            for(var i=0;i<tratte.length;i++){
                if(tratte[i].id==id)
                {
                    $("#linee").append("<tr>"+tratte[i].row+"<tr/>");
                    $(this).parent().parent().parent().next().remove();
                    $(this).parent().parent().parent().remove();
                    tratte[i].stopped=true;
					//stoppa tratta sul DB
                    var params;
                    params = new FormData();
                    params.append( 'IDTratta', tratte[i].idTratta);
                   $.ajax({
                    type: 'POST',
                    url: "http://bustracker.altervista.org/Simulatore/StopTratta.php",
                    data: params,
                    processData: false,
                    contentType: false,
                    dataType:"html",
                    async:false
                    });
                    ///////////////////////
                    tratte.splice(i,1);
                    break;
                }
            }
        });
    });
});
