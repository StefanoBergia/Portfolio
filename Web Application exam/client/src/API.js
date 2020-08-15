import Car from "./Car.js";

async function getCarList(){
    const response=await fetch("/api/carlist");
    const carlist_json=await response.json();
    if(response.ok){
        return carlist_json.map((row)=>Car.from(row));
    }else{
        let err={error:response.status}
        throw err;
    }
}

async function userLogin(username,password){
    return new Promise((resolve,reject)=>{
        fetch("/api/login",{
            method:'POST',
            headers:{
                'Content-Type':'application/json'
            },
            body:JSON.stringify({username:username,password:password})
        }).then((response)=>{
            if(response.ok){
                response.json()
                .then((obj)=>{
                    resolve(obj);
                })
                .catch((err)=>{
                    reject({errors:[{param:"Application",msg:"Cannot parse server resonse"}]});
                });
            }else{
                response.json()
                .then((obj)=>{reject(obj);})
                .catch((err)=>{
                    reject({errors:[{param:"Application",msg:"Cannot parse server resonse"}]});
                });
            }
        })
        .catch((err)=>{
            reject({errors:[{param:"Server",msg:"Cannot communicate"}]});
        })
    });
}

async function userLogout(username,password){
    return new Promise((resolve,reject)=>{
        fetch("/api/logout",{
            method:'POST'
        }).then((response)=>{
            if(response.ok){
                resolve(null);
            }else{
                response.json()
                .then((obj)=>{reject(obj);})
                .catch((err)=>{
                    reject({errors:[{param:"Application",msg:"Cannot parse server resonse"}]});
                });
            }
        })
        .catch((err)=>{
            reject({errors:[{param:"Server",msg:"Cannot communicate"}]});
        })
    });
}

async function getNumberandPrice(params){
    let query = "";
    for (let key in params) {
        query += encodeURIComponent(key)+"="+encodeURIComponent(params[key])+"&";
    }
    const response=await fetch("/api/book?"+query);
    const carlist_json=await response.json();
    if(response.ok){
        return carlist_json;
    }else{
        let err={error:response.status}
        throw err;
    }
}

async function submitRequest(params){
    return new Promise((resolve,reject)=>{
        fetch("/api/confirm", {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                user:params.user,
                insurrance:params.insurrance,
                startDate:params.startDate,
                endDate:params.endDate,
                category:params.category,
                ageRange:params.ageRange,
                drivers:params.drivers,
                km:params.km
            })
        }).then((response)=>{
            response.json().then((obj)=>{
                resolve(obj);
            }).catch((err)=>reject(err));;
        })
        .catch((err)=>{
            console.log(JSON.stringify(err));
            reject(err);
        });
    });

}

async function confirmPayment(params){
    return new Promise((resolve,reject)=>{
        fetch('/api/confirm', {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                id:params.id,
                cardnumber:params.cardnumber,
                ccv:params.ccv,
                completename:params.completename
            })
        }).then((response)=>{
            response.json().then((obj)=>{
                resolve(obj);
            }).catch((err)=>{
                reject(err);
            });
        })
        .catch((err)=>{
            reject(err);
        });
    });
}

async function deleteRequest(id) {
    console.log(id);
    return new Promise((resolve, reject) => {
        fetch("/api/confirm/" + id, {
            method: 'DELETE',
        }).then((response)=>{
            response.json().then((obj)=>{
                resolve(obj);
            }).catch((err)=>{
                reject(err);
            });
        })
        .catch((err)=>{
            reject(err);
        });
    });
}

async function getRentHistory(){
    const response=await fetch("/api/renthistory");
    const list_json=await response.json();
    if(response.ok){
        return list_json;
    }else{
        let err={error:response.status}
        throw err;
    }
}

async function getLoggeduser(){
    const response=await fetch("/api/loggeduser")
    const obj=await response.json();
    if(response.ok){
        return obj;
    }else{
        let err={error:response.status}
        throw err;
    }
}

const API={getCarList,userLogin,userLogout,getNumberandPrice,submitRequest,confirmPayment,deleteRequest,getRentHistory,getLoggeduser};
export default API;