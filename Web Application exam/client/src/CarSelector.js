import React from 'react';
import CarTable from './CarTable';
import CarFilter from './CarFilter';
import Car from "./Car.js";

class CarSelector extends React.Component{

    constructor(props){
        super(props);
        /*
        carlist->elenco delle auto visualizzate
        first_filter_brand->prima volta che si applica il filto sulle marche dopo il reset,
        first_filter_cat->prima volta che si applica il filto sulle categories dopo il reset,
        count_cat->numero di filtri categoria,
        count_brand->numero di filtri su marca};
        */
        this.state={carlist:[],first_filter_brand:true,first_filter_cat:true,count_cat:0,count_brand:0};
        this.filterCat=this.filterCat.bind(this);
        this.filterBrand=this.filterBrand.bind(this);
        this.removeCat=this.removeCat.bind(this);
        this.removeBrand=this.removeBrand.bind(this);
        this.showAll=this.showAll.bind(this);
    }

    //recupero la lista delle automobili solo nel component did mount
    async componentDidMount(){
        let ret;
        ret=await this.props.getCarList();
        if(!ret.error){
            this.setState({carlist:ret});
        }
    }

    getCategories=function(){
        let cat=[];
       cat=this.state.carlist
            .map((c)=>c.categoria)
            .filter((value,index,self)=>self.indexOf(value)===index)
            .sort()
        return cat;
    }

    getBrands=function(){
        let brands=[];
        brands=this.state.carlist
             .map((c)=>c.marca)
             .filter((value,index,self)=>self.indexOf(value)===index)
             .sort();
         return brands;
    }

    //resetta i flag visibleCat e visibleBrand per tutte le categorie
    showAll=function(){
        let newlist=this.state.carlist.map((c)=>{
            let nc=Car.from(c);
            nc.visibleCat=true;
            nc.visibleBrand=true;
            return nc;
        });
        this.setState({carlist:newlist,first_filter_brand:true,first_filter_cat:true,count_cat:0,count_brand:0});
    }


    //aggiunge una categoria al filtro
    filterCat=function (cat){
        let newlist=this.state.carlist.map((c)=>{
            let nc=Car.from(c);
            if(nc.categoria===cat )
                nc.visibleCat=true;
            else if(this.state.first_filter_cat)
                nc.visibleCat=false;
            return nc;
        });
        this.setState((prev)=>({count_cat:prev.count_cat+1}));
        this.setState({carlist:newlist,first_filter_cat:false});
    }

    //rimuove una categoria dal filtro
    removeCat=function (cat){

        let newlist=this.state.carlist.map((c)=>{
            let nc=Car.from(c);
            if(nc.categoria===cat && this.state.count_cat>1)
                nc.visibleCat=false;
            else if(this.state.count_cat===1)
                nc.visibleCat=true;
            return nc;
        });
        if(this.state.count_cat===1)
            this.setState({first_filter_cat:true});

        this.setState((prev)=>({count_cat:prev.count_cat-1}));
        this.setState({carlist:newlist});
    }

    //aggiunge una marca al filtro
    filterBrand=function (brand){    
        let newlist=this.state.carlist.map((c)=>{
            let nc=Car.from(c);
            if(  nc.marca===brand )
                nc.visibleBrand=true;
            else if(this.state.first_filter_brand)
                nc.visibleBrand=false;
            return nc;
        });
        this.setState((prev)=>({count_brand:prev.count_brand+1}));
        this.setState({carlist:newlist,first_filter_brand:false});
    }

    //rimuove una marca dal filtro
    removeBrand=function (brand){
       
        let newlist=this.state.carlist.map((c)=>{
            let nc=Car.from(c);
            if(  nc.marca===brand && this.state.count_brand>1)
                nc.visibleBrand=false;
            else if(this.state.count_brand===1)
                nc.visibleBrand=true;
            return nc;
        });
        if(this.state.count_brand===1)
            this.setState({first_filter_brand:true});
        this.setState((prev)=>({count_brand:prev.count_brand-1}));
        this.setState({carlist:newlist});
    }

    render(){
        return (
            <div className='d-flex justify-content-center ' style={{"padding":"3%"}}>
            <CarTable carlist={this.state.carlist}/>
            <CarFilter 
            categories={this.getCategories()} 
            brands={this.getBrands()} 
            filterCat={this.filterCat} 
            filterBrand={this.filterBrand} 
            removeCat={this.removeCat} 
            removeBrand={this.removeBrand} 
            first_filter_brand={this.state.first_filter_brand} 
            first_filter_cat={this.state.first_filter_cat} 
            resetAll={this.showAll} />
            </div>
        );
    }
}

export default CarSelector;