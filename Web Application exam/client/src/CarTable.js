import React from 'react';


class CarTable extends React.Component{

   render(){
       return <div className="p-4" style={{'width':'130%'}}> 
       <h4>Elenco Veicoli</h4>
       <table className='table table-striped'>
           <thead className="thead-dark ">
               <tr>
                   <th >Marca</th>
                   <th >Modello</th>
                   <th >Categoria</th>
                   <th >Numero di veicoli</th>
               </tr>
           </thead>

           <tbody >
               {
                this.props.carlist.filter((e)=>(e.visibleCat && e.visibleBrand)).map((e)=>{
                   return( <tr key={e.marca+e.modello}>
                        <td>
                            {e.marca}
                        </td>
                        <td>
                            {e.modello}
                        </td>
                        <td>
                            {e.categoria}
                        </td>
                        <td>
                            {e.n}
                        </td>
                    </tr>);
                   }
               )}
            
           </tbody>

       </table>
       {
           this.props.carlist.filter((e)=>(e.visibleCat && e.visibleBrand)).length===0 ? (<div className="alert alert-primary" role="alert">Nessuna auto soddisfa i filtri di ricerca</div>):<div></div>
       }
       </div>
   }

}

export default CarTable;