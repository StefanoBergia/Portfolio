import React from 'react';

class CarFilter extends React.Component{


    render(){
        return <>
                     
                    <div className="p-4">
                        <h4>Filtra categorie</h4>
                        
                       {
                            this.props.categories.map((c)=><>                  
                         <FilterCheckBox  
                         key={c}  
                         value={c} 
                         checked={false} 
                         first_filter={this.props.first_filter_cat} 
                         applyFilter={this.props.filterCat} 
                         removeFilter={this.props.removeCat} />
                         
                        </>

                       )}

                        <button className="btn btn-primary" style={{"margin-top":"20%"}} onClick={this.props.resetAll}>Reset Filtri</button>
                    </div>
                    <div className="p-4">
                        <h4>Filtra marche</h4>
                       {
                            this.props.brands.map((c)=><> 
                         <FilterCheckBox  
                         key={c}  
                         value={c} 
                         checked={false} 
                         first_filter={this.props.first_filter_brand} 
                         applyFilter={this.props.filterBrand} 
                         removeFilter={this.props.removeBrand }  />
                         
                        </>
                        )}

                        
                    </div>
            </>
    }
}

class FilterCheckBox extends React.Component{

    constructor(props){
        super(props);
        this.state={value:props.value, checked:this.props.checked, applyFilter:this.props.applyFilter,  removeFilter:this.props.removeFilter, hideAll:this.props.hideAll}
       
      
        this.toggle=this.toggle.bind(this);
    }

    componentDidUpdate(prevProps, prevState) {
        //update dello stato di checked quando si preme il pulsante reset
        if (prevProps.first_filter !== this.props.first_filter && prevProps.first_filter===false) {
          this.setState({checked:false});
        }
      }

    //cambio di stato e applicazione del filtro nel momento in cui si fa click sulla checkbox
    toggle=function(){
        if(this.props.first_filter){
            this.state.applyFilter(this.state.value);
            this.setState({checked:true});
        }else{
            
            console.log("toggled");
            if(this.state.checked){
                this.state.removeFilter(this.state.value);
                this.setState({checked:false});
            }else{
                //caso di reset
                this.state.applyFilter(this.state.value);
                this.setState({checked:true});
            }
        }
    }

    render(){
        return <>
            <div  className="custom-control custom-checkbox form-check">
            <input type="checkbox" className= "custom-control-input checked" id={"check-"+this.state.value}   checked={this.state.checked} onChange={this.toggle} />
            <label className="custom-control-label" htmlFor={"check-" +  this.state.value}>{this.state.value}</label>
            </div>
            </>
    }
}

export default CarFilter;