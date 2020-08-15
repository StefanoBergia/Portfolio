

const moment=require('moment');

dayprices={'A':80,'B':70,'C':60,'D':50,'E':40};

//prezzo base con numero di giorni
getBasePrice=function(startDate,endDate,category){
    return (moment(endDate).diff(startDate,'days')*this.dayprices[category]);
}

discountKm=function(km){
    switch(km){
        case '1':
            return 1-1*0.05;
        case  '3':
            return 1+1*0.05;
        default:
            return 1;
    }
}

discountAge=function(age){
    switch(age){
        case '1':
            return 1+1*0.05;
        case  '3':
            return 1+1*0.1;
        default:
            return 1;
    }
}

discountDriver=function( drivers){
    if(parseInt(drivers)>0)
        return 1+1*0.15;
    else
        return 1;
}

discountInsurrance=function( ins){
    if(ins==="true"){
        return 1+1*0.2;
    }
    else
        return 1;
}

discountFew=function( tot,cur){
    if(cur<0.1*tot)
        return 1+1*0.1;
    else
        return 1;
}

discountClient=function( count){
    if(count>=3)
        return 1-1*0.1;
    else
        return 1;
}

exports.computePrice=function(params){
    let price=getBasePrice(params.startDate,params.endDate,params.category);

    price=price*discountKm(params.km);
    price=price*discountAge(params.ageRange);
    price=price*discountDriver(params.drivers);
    price=price*discountInsurrance(params.insurrance);
    price=price*discountFew(params.tot,params.cur);
    price=price*discountClient(params.client);
    return Math.round(price * 10) / 10;
}