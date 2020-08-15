const express = require('express');
const dao = require('./dao');
const morgan = require('morgan');
const jwt=require('express-jwt');
const jsonwebtoken=require('jsonwebtoken');
const cookieParser=require('cookie-parser');
const moment=require('moment');


const jwtSecret = '6xvL4xkAAbG49hcXf5GIYSvkDICiUAR6EdR5dLdwW7hMzUjjMUe9t6M5kSAYxsvX';
const expireTime = 600; //seconds

const PORT = 3001;

const app = express();

app.use(morgan('tiny'));
app.use(express.json());


app.get('/api/carlist',(req,res)=>{
    dao.getCarList()
        .then((car_list)=>{
            res.json(car_list);
        })
        .catch((err)=>{
            res.status(400).json({
                errors:[{'msg':err}]
            });
        });
});

app.post('/api/login',(req,res)=>{
    const username=req.body.username;
    const password=req.body.password;


    dao.getUser(username)
        .then((user)=>{
            
            if(user===undefined){
                res.status(401).send({
                    errors:[{'param':'Server','msg':'Invalid username'}]
                });
            }else{
                if(!dao.checkPassword(password,user.password)){
                    res.status(401).send({
                        errors:[{'param':'Server','msg':'Wrong password'}]
                    });
                }else{
                    const token=jsonwebtoken.sign({user:user.username},jwtSecret,{expiresIn:expireTime});
                    res.cookie('token',token,{httpOnly:true,sameSite:true,maxAge:1000*expireTime});
                    res.json({username:user.username});
                }
            }
        }).catch(
            (err)=>{
                
                new Promise((resolve)=>{
                    setTimeout(resolve,1000)
                }).then(()=>res.status(401).json(
                    {errors:[{'param':'Server','msg':'Authorization error'}]}
                ));
            }
        );
});

app.use(cookieParser());

app.post('/api/logout',(req,res)=>{
    res.clearCookie('token').end();
});

app.use(
    jwt({
        secret:jwtSecret,
        getToken:req=>req.cookies.token
    })
);


app.get('/api/book',(req,res)=>{
    const user=req.user && req.user.user;
    const params={
        user:user,
        insurrance:req.query.insurrance,
        startDate:req.query.startDate,
        endDate:req.query.endDate,
        category:req.query.category,
        ageRange:req.query.ageRange,
        drivers:req.query.drivers,
        km:req.query.km
    }

    err=validateCarReq(params);
    if(err){
        res.status(400).json(err);
    }else{


        dao.getCarCount(params).then((obj)=>{
            res.json({count:obj.count,price:obj.price});
        }).catch((e)=>{
            res.status(400).json({errors:[{'param':'Server','msg':'Unexpected error'}]});
        });
    }

});

app.post('/api/confirm',(req,res)=>{
    const user=req.user && req.user.user;
   
    let params={
        user:user,
        insurrance:req.body.insurrance,
        startDate:req.body.startDate,
        endDate:req.body.endDate,
        category:req.body.category,
        ageRange:req.body.ageRange,
        drivers:req.body.drivers,
        km:req.body.km
    }
    err=validateCarReq(params);
   
    if(err){
        res.status(400).json(err);
    }else{


        dao.getCarCount(params).then((obj)=>{
            dao.insertRequest({car_id:obj.id,
                               username:user,
                               data_inizio:params.startDate,
                               data_fine:params.endDate,
                               n_guidatori:params.drivers,
                               eta_guidatore:params.ageRange,
                               assicurazione:params.insurrance,
                               km_stimati:params.km})
                               .then((id)=>{
                                    res.json({  
                                        req_id:id,
                                        carid:obj.id,
                                        marca:obj.marca,
                                        categoria:obj.categoria,
                                        modello:obj.modello,
                                        count:obj.count,
                                        price:obj.price});
                               })
                               .catch((e)=>{
                                
                                res.status(400).json({errors:[{'param':'Server','msg':'Unexpected error'}]});
                            });
            
            
        }).catch((e)=>{
            
            res.status(400).json({errors:[{'param':'Server','msg':'Unexpected error'}]});
        });
    }
});

app.put('/api/confirm',(req,res)=>{
    const user=req.user && req.user.user;
    if(!req.body.id){
        res.status(400).end();
    }else{
        const params={
            id:req.body.id,
            cardnumber:req.body.cardnumber,
            ccv:req.body.ccv,
            completename:req.body.completename
        }
        
        if(validateCard(params)){
            dao.confirmRequest(params.id,user)
            .then((ok)=>res.json({msg:"OK"}))
            .catch((err)=>{
                res.status(400).json({errors:[{'param':'Server','msg':'Unexpected error'}]});
            });
        }else{
            
            res.status(400).json({errors:[{'param':'Server','msg':'Parameter error'}]});
        }
    }
});

app.delete('/api/confirm/:id',(req,res)=>{
    const user=req.user && req.user.user;
  
    if(!req.params.id){
        res.status(400).end();
    }else{
        dao.deleteRequest(req.params.id,user)
        .then((ok)=>res.json({msg:"OK"}))
        .catch((err)=>{
            res.status(400).json({errors:[{'param':'Server','msg':'Unexpected error'}]});
        });
    }
});

app.get('/api/renthistory',(req,res)=>{
    const user=req.user && req.user.user;
    dao.getRentHistory(user)
        .then((list)=>{
            res.json(list);
        })
        .catch((err)=>{
            res.status(400).json({
                errors:[{'msg':err}]
            });
        });
});

app.get('/api/loggeduser',(req,res)=>{
    const user=req.user && req.user.user;
    res.json({username:user});
});

function validateCarReq(params){

    msg=[];

    if( !(moment(params.startDate).isAfter(moment().add(-1,'days').format("yyyy-MM-DD"),'day')
            &&  moment(params.endDate).isAfter(params.startDate,'day'))){
                msg.push('Date error');
    }


    if(!(params.category=='A' ||
        params.category=='B' ||
        params.category=='C' ||
        params.category=='D' ||
        params.category=='E' )){
            msg.push('Category error');
    }

    if(!(params.ageRange=='1' ||
    params.ageRange=='2' ||
    params.ageRange=='3'  )){
        msg.push('Age Range error');
    }


    if(!(params.km=='1' ||
    params.km=='2' ||
    params.km=='3'  )){
        msg.push('km error');
    }

    if(!(params.drivers=='0' ||
    params.drivers=='1' ||
    params.drivers=='2' ||
    params.drivers=='3' ||
    params.drivers=='4' )){
        msg.push('km error');
    }

    if(msg.length>0)
     return {errors:[{'param':'Server','msg':msg}]}
    else
        return null;
    
}

function validateCard(params){
    if(params.cardnumber && params.ccv && params.completename ){
        if(params.cardnumber.match(/\b\d{16}\b/g) 
            && params.ccv.match(/\b\d{3}\b/g)
            && params.completename.trim().includes(" "))
        {
            return true;
        }
    }
        return false;
}

app.listen(PORT, ()=>console.log(`Server running on http://localhost:${PORT}/`));