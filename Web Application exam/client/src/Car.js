class Car{
    
    constructor(modello,marca,categoria,n){
        this.modello=modello;
        this.marca=marca;
        this.categoria=categoria;
        this.n=n;
        this.visibleCat=true;
        this.visibleBrand=true;
    }

    static from(json){
        return Object.assign(new Car(),json);
    }
}



export default Car;