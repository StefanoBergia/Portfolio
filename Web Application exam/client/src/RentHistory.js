import React from 'react';
import { Redirect } from 'react-router-dom';
import moment from 'moment';

class RentHistory extends React.Component{
    constructor(props){
        super(props);
        this.state={listPast:[],listPresent:[],listFuture:[],APIerror:false};
        this.deleteRent=this.deleteRent.bind(this);
    }

    componentDidMount(){
        this.updateList();
    }

    //tramite API recupera la lista delle prenotazioni dell'utente e le splitta nelle tre liste
    updateList=async function(){
        let ret;
        let listPast=[];
        let listPresent=[];
        let listFuture=[];
        ret=await this.props.getRentList();
        ret=ret.sort((a,b)=>
             moment(a.data_inizio).isAfter(b.data_inizio) ? -1:1
        );
        if(!ret.error){
            for(let e of ret){
                if(moment().isAfter(e.data_fine))
                    listPast.push(e);
                else if (moment().isSameOrAfter(e.data_inizio) && moment().isSameOrBefore(e.data_fine))
                    listPresent.push(e);
                else
                    listFuture.push(e);
            }
            this.setState({listPast,listPresent,listFuture,APIerror:false});
        }else{
            if(!this.props.getCookie('token')){
                this.props.resetUser();
                return;
            }else{
                this.setState({listPast:[],listPresent:[],listFuture:[]});
            }
            this.setState({APIerror:true});
        }
    }

    //elimina una prenotazione futura
    deleteRent=function(id){
        this.props.deleteRent(id).then((obj)=>
            this.updateList()
        ).catch((err)=>{
            if(!this.props.getCookie('token')){
                this.props.resetUser();
                return;
            }else{
                this.setState({listPast:[],listPresent:[],listFuture:[],APIerror:true});
            }
            this.setState({APIerror:true});
        });

    }

    render(){
        return <div  style={{"padding":"3%","margin-top":"60px"}}>
                {!this.props.authUser && <Redirect to="/login/storico"/>}
                <h2>Noleggi di {this.props.authUser}</h2>
                <hr/>
                {
                    this.state.APIerror===true &&
                    <div>
                        <div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">Problema di comunicazione col server</div>
                        <hr/>
                    </div>
                }
                <h3>Noleggi futuri</h3>
                <HistoryTable list={this.state.listFuture} delete='true' deleteRent={this.deleteRent} />
                <h3>Noleggi in corso</h3>
                <HistoryTable list={this.state.listPresent}  />
                <h3>Noleggi Passati</h3>
                <HistoryTable list={this.state.listPast} />
            </div>
    }
}

const HistoryTable = (props) =>{
    return <div className="p-4" > 
       <table className='table table-striped'>
           <thead className="thead-dark ">
               <tr>
                   <th >Targa</th>
                   <th >Modello</th>
                   <th >Marca</th>
                   <th >Categoria</th>
                   <th >Data inizio</th>
                   <th >Data fine</th>
                   <th >Guidatori addizionali</th>
                   <th >Età guidatore</th>
                   <th >Km giornalieri</th>
                   <th >Assicurazione</th>
                   {props.delete &&  <th>Elimina</th>}
               </tr>
           </thead>

           <tbody >
               {
                props.list.map((e)=>{
                   return( <tr key={e.id}>
                        <td>
                            {e.car_id}
                        </td>
                        <td>
                            {e.modello}
                        </td>
                        <td>
                            {e.marca}
                        </td>
                        <td>
                            {e.categoria}
                        </td>
                        <td>
                            {e.data_inizio}
                        </td>
                        <td>
                            {e.data_fine}
                        </td>
                        <td>
                            {e.n_guidatori}
                        </td>
                        <td>
                            {e.eta_guidatore===1 && "meno di 25 anni"}
                            {e.eta_guidatore===2 && "tra 25 e 65 anni"}
                            {e.eta_guidatore===3 && "più di 65 anni"}
                        </td>
                        <td>
                            {e.km_stimati===1 && "meno di 50 km"}
                            {e.km_stimati===2 && "tra 50 km e 150 km"}
                            {e.km_stimati===3 && " km illimitati"}
                        </td>
                        <td>
                            {e.assicurazione ===1 ? "si":"no"}
                        </td>
                         {/*Pulsante elimina */}
                        { props.delete &&  
                            <td>
                                <div onClick={()=>{
                                    props.deleteRent(e.id)
                                    }}>
                                    <svg className="bi bi-trash-fill" width="1em" height="1em" viewBox="0 0 16 16" fill="currentColor" xmlns="http://www.w3.org/2000/svg">
                                        <path fillRule="evenodd" d="M2.5 1a1 1 0 0 0-1 1v1a1 1 0 0 0 1 1H3v9a2 2 0 0 0 2 2h6a2 2 0 0 0 2-2V4h.5a1 1 0 0 0 1-1V2a1 1 0 0 0-1-1H10a1 1 0 0 0-1-1H7a1 1 0 0 0-1 1H2.5zm3 4a.5.5 0 0 1 .5.5v7a.5.5 0 0 1-1 0v-7a.5.5 0 0 1 .5-.5zM8 5a.5.5 0 0 1 .5.5v7a.5.5 0 0 1-1 0v-7A.5.5 0 0 1 8 5zm3 .5a.5.5 0 0 0-1 0v7a.5.5 0 0 0 1 0v-7z"/>
                                    </svg>
                                
                                </div >
                            </td>
                        }
                    </tr>);
                   }
               )}
            
           </tbody>

       </table>
       {
           props.list.length===0 ? (<div className="alert alert-primary" role="alert">Nessuna dato da visualizzare</div>):<div></div>
       }
       </div>
}

export default RentHistory;