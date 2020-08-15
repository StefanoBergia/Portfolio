
//classe che funge da filtro tra DB e API
class Car{
    constructor(modello,marca,categoria,n){
        this.modello=modello;
        this.marca=marca;
        this.categoria=categoria;
        this.n=n;
    }
}

module.exports=Car;