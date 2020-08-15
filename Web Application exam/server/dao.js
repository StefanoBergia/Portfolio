'use strict';

const Car=require('./car');
const sqlite=require('sqlite3').verbose();
const bcrypt=require('bcrypt');
const coefficients=require('./coefficients');

//una volta al minuto elimino le prenotazioni non confermate entro 10 minuti
setInterval(()=>{ 
    const sql="DELETE FROM noleggio WHERE  confirmed='false' and timestamp +600000<?";
    db.run(sql,[new Date().getTime()],
        function(err){
            if(err){
                console.log("Record cleanup error "+err);
            }
            else
                console.log("Record cleanup done");
        });
 }, 60000);

//apro la connessione col db
const db=new sqlite.Database('./auto_noleggio',(err)=>{
   if(err){
        console.error(err.message);
        throw err;
   }
});

//restituisce l'elenco di modelli con relativo numero di veicoli
exports.getCarList=function(){
    return new Promise((resolve,reject)=>{
        const query="SELECT marca,modello,categoria,COUNT(*) as q FROM car GROUP BY marca,modello,categoria";
        db.all(query,(err,rows)=>{
            if(err)
                reject(err);
            else {
                const car_array=[];
                for(let row of rows){
                    car_array.push(new Car(row.modello,row.marca,row.categoria,row.q));
                }
                resolve(car_array);
            }
        });
    });
}

//verifica l'esistenza di un username
exports.getUser=function(username){
    return new Promise(
        (resolve,reject)=>{
            const sql="SELECT * FROM user WHERE username= ?";
            db.all(sql,[username],(err,rows)=>{
                    if (err){
                        reject(err);
                    }
                    else if(rows.length===0){
                        resolve(undefined)
                    }else {
                        const user={username:rows[0].username,password:rows[0].password};
                        resolve(user);
                    }
                }
            );
        }
    );
}

//restituisce numero di veicoli disponibili e calcola il prezzo
exports.getCarCount=function(params){
    return new Promise( (resolve,reject)=>{

        let sel={id:null,marca:null,categoria:null,modello:null,count:0,price:0};
        let tot_cat=0;
        let client=0;
        //conta numero di noleggi per l'utente
        let sql="SELECT COUNT(*) as c from noleggio WHERE username=?";
        db.all(sql,[params.user],(err,rows)=>{
            if(err){
                reject(err);
            }else{
                client=rows[0].c;
            }
        });

        //conta numero totale di veicoli per una data categoria
        sql="SELECT COUNT(*) as c from car WHERE categoria=?";
        db.all(sql,[params.category],(err,rows)=>{
            if(err){
                reject(err);
            }else{
                tot_cat=rows[0].c;
            }
        });
        sql="SELECT id, marca,modello,categoria FROM car"+
                " WHERE categoria=? AND id NOT IN "+ 
                    "(SELECT car_id FROM noleggio"+
                    " WHERE categoria=? AND "+
                    " ("+
                    " (data_inizio<=datetime(?) AND data_fine>=datetime(?))"+ 
                    " OR (data_inizio>=datetime(?) AND data_fine<=datetime(?))"+
                    " OR (data_inizio<=datetime(?) AND data_fine>=datetime(?))"+
                    " OR (data_inizio<=datetime(?) AND data_fine>=datetime(?))"+
                "))";

            
        db.all(sql,[params.category,
                    params.category,
                    params.startDate,
                    params.endDate,
                    params.startDate,
                    params.endDate
                    ,params.startDate
                    ,params.startDate
                    ,params.endDate
                    ,params.endDate],(err,rows)=>{
            if(err){
                reject(err);
            }
            else{
                
                sel.count=rows.length;
                if(sel.count>0){
                    sel.id=rows[0].id;
                    sel.marca=rows[0].marca;
                    sel.categoria=rows[0].categoria;
                    sel.modello=rows[0].modello;
                }else {
                    sel.id=null;
                    sel.marca=null;
                    sel.categoria=null;
                    sel.modello=null;
                }
                //calcolo del prezzo
                sel.price=coefficients.computePrice({
                    ...params, tot:tot_cat,cur:sel.count,client:client
                });


                resolve(sel);
            }
        });
    });
}

//inserisce una richiesta nel DB (confirmed=alse)
exports.insertRequest=function(params){
    return new Promise( (resolve,reject)=>{
    const sql="INSERT INTO noleggio (car_id,username,data_inizio,data_fine,n_guidatori,eta_guidatore,assicurazione,km_stimati,confirmed,timestamp) "+
                                " VALUES(?,?,?,?,?,?,?,?,'false',?)"
    db.run(sql,[params.car_id,params.username,params.data_inizio,params.data_fine,params.n_guidatori,params.eta_guidatore,params.assicurazione,params.km_stimati,new Date().getTime()],
        function(err){
            if(err){
                reject(err);
            }
            else
                resolve(this.lastID);
        });
    });
}

//conferma una richiesta
exports.confirmRequest=function(id,username){
    return new Promise( (resolve,reject)=>{
        const sql="UPDATE noleggio SET confirmed='true' WHERE id=? and username=?";
        db.run(sql,[id,username],
            function(err){
                if(err){
                    reject(err);
                }
                else
                    resolve("OK");
            });
        });
}

//elimina una richiesta
exports.deleteRequest=function(id,username){
    return new Promise( (resolve,reject)=>{
        const sql="DELETE FROM noleggio WHERE id=? and  username=? ";
        db.run(sql,[id,username],
            function(err){
                if(err){
                    reject(err);
                }
                else
                    resolve("OK");
            });
        });
}

//recupera elenco dei noleggi confermati di un utente
exports.getRentHistory=function(username){
    return new Promise((resolve,reject)=>{
        const query="SELECT noleggio.id as id,car_id,marca,modello,categoria,data_inizio,data_fine,n_guidatori,eta_guidatore,assicurazione,km_stimati FROM noleggio,car WHERE car.id=noleggio.car_id AND username=? and confirmed='true' ";
        db.all(query,[username],(err,rows)=>{
            if(err)
                reject(err);
            else {
                resolve(rows);
            }
        });
    });
}

//verifica due password cryptate
exports.checkPassword=function(clearpwd,password){
    return bcrypt.compareSync(clearpwd,password);
}