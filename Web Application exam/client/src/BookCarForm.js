import React from 'react';
import { Redirect } from 'react-router-dom';
import moment from 'moment';


class BookCarForm extends React.Component{
    constructor(props){
        super(props);
        /*
            authUser:utente attualmente loggato
            mode: può assumere valori "filter" per visualizzare il form di prenotazione e "pay" per visualizzare il form di pagamento
            dateError,APIerror,CardError flag per la visualizzazione di messaggi di errore
            ...
            dati dei form
            ...
            prenotazione: oggetto contenente i dati di prenotazione, generato nel passaggio da "filter" e "pay"
        */
        this.state={authUser:this.props.user,mode:"filter",dateError:false,APIerror:false,CardError:"none",

            checked:false,
            startDate:moment().add(1,'days').format("yyyy-MM-DD"),
            endDate:moment().add(3,'days').format("yyyy-MM-DD"),
            selectCategory:"A",
            eta:"1",
            selectGuidatori:"0",
            km:"1",

            cardnumber:"",
            ccv:"",
            completename:"",

            carCount:0,
            price:0,

            prenotazione:null

        };
        this.toggle=this.toggle.bind(this);
        this.submitRequest=this.submitRequest.bind(this);
        this.validatePayment=this.validatePayment.bind(this);
        this.cancelRequest=this.cancelRequest.bind(this);
    }

    componentDidMount(){
        this.updateNumber();
    }

    componentDidUpdate(prevProps,prevState){
        //verifico se è cambiato un campo
        if(prevState.checked!==this.state.checked ||
            prevState.startDate!==this.state.startDate ||
            prevState.endDate!==this.state.endDate ||
            prevState.selectCategory!==this.state.selectCategory ||
            prevState.eta!==this.state.eta ||
            prevState.selectGuidatori!==this.state.selectGuidatori ||
            prevState.km!==this.state.km)
                this.updateNumber();
    }

    updateField=(name,value)=>{
        this.setState({[name]:value});
    }

    validateForm=(event)=>{
        event.preventDefault();
    }

    toggle=function(){
        this.setState((prev)=>{return {checked:!prev.checked};})
    }

    //visualizza il numero di auto disponibili e il prezzo
    updateNumber = function(){
        //validazione delle date
        if( moment(this.state.startDate).isAfter(moment().add(-1,'days').format("yyyy-MM-DD"),'day')
            &&  moment(this.state.endDate).isAfter(this.state.startDate,'day')){
                this.setState({dateError:false});
                this.props.getNumberandPrice({
                    insurrance:this.state.checked,
                    startDate:this.state.startDate,
                    endDate:this.state.endDate,
                    category:this.state.selectCategory,
                    ageRange:this.state.eta,
                    drivers:this.state.selectGuidatori,
                    km:this.state.km
                }).then((res)=>{
                    this.setState({APIerror:false,carCount:res.count,price:res.price});
                }).catch((err)=>{
                    this.setState({APIerror:true,carCount:0,price:0});
                    //se l'access token è scaduto torno alla pagina di login
                    if(!this.props.getCookie('token')){
                        this.setState({authUser:null,prenotazione:null});
                        this.props.resetUser();
                        return;
                    }
                });
        }else{
            this.setState({dateError:true,APIerror:false,carCount:0,price:0});
        }
    }

    //invia la richiesta di prenotazione
    submitRequest=function(){
        
        this.props.submitRequest({
            insurrance:this.state.checked,
            startDate:this.state.startDate,
            endDate:this.state.endDate,
            category:this.state.selectCategory,
            ageRange:this.state.eta,
            drivers:this.state.selectGuidatori,
            km:this.state.km
        }).then((res)=>{
            //cambio modalità di visualizzazione nella pagina
            this.setState({prenotazione:res,mode:"pay"});
        }).catch((err)=>{
            this.setState({APIerror:true,carCount:0,price:0});
            //se l'access token è scaduto torno alla pagina di login
            if(!this.props.getCookie('token')){
                this.setState({authUser:null,prenotazione:null});
                this.props.resetUser();
                return;
            }
        });
    }

    //validazione dati del form della carta di credito 
    validatePayment=function(){
        if(this.state.cardnumber && this.state.ccv && this.state.completename){
            if(!this.state.cardnumber.match(/\b\d{16}\b/g) )
            {
                this.setState({CardError:"card"});
                return;
            }
            if(!this.state.ccv.match(/\b\d{3}\b/g) )
            {
                this.setState({CardError:"ccv"});
                return;
            }
            if(!this.state.completename.trim().includes(" ") )
            {
                this.setState({CardError:"name"});
                return;
            }
            this.setState({CardError:"none"});
            this.submitPayment();
        }else{
            this.setState({CardError:"all"});
        }
    }

    //invia dati di pagamento per confermare la prenotazione
    submitPayment=function(){
        this.props.confirmPayment({
            //id della prenotazione, restituito dall'api di richiesta di prenotazione
            id:this.state.prenotazione.req_id,
            cardnumber:this.state.cardnumber,
            ccv:this.state.ccv,
            completename:this.state.completename
        })
        .then((res)=>{
            this.setState({CardError:"none"});
            this.props.done();
        })
        .catch((err)=>{
            this.setState({CardError:"server"});
            //se l'access token è scaduto torno alla pagina di login
            if(!this.props.getCookie('token')){
                this.setState({authUser:null,prenotazione:null});
                this.props.resetUser();
                return;
            }
        });
    }

    //annullo la richiesta di prenotazione in caso
    cancelRequest=function(){
        this.props.deleteRequest(this.state.prenotazione.req_id)
        .then((res)=>{
            this.setState({CardError:"none",mode:"filter",prenotazione:null});
        })
        .catch((err)=>{
            this.setState({CardError:"server"});
            //se l'access token è scaduto torno alla pagina di login
            if(!this.props.getCookie('token')){
                this.setState({authUser:null,prenotazione:null});
                this.props.resetUser();
                return;
            }
        });

    }

    render(){
            return<>
            {/* se l'utente non è autenticato si fa il redirect su /login/prenota*/}
            {!this.state.authUser? <Redirect to="/login/prenota"/>:<h2>this.state.authUser</h2>}
            {this.state.mode==="filter"? 
             (<div className='d-flex justify-content-center ' style={{"margin-top":"100px"}}>
                 
                <form className='' method={'POST'}
                onSubmit={this.validateForm} ref={form=>this.form=form}>
                   <h2 className="p-2" >Inserisci i parametri per la prenotazione</h2>
                   <div className="d-flex justufy-content-center" style={{"width":"150%"}}>
                        <div className="container">
                            <div className="row">
                                <div className="col-sm">
                                    <label htmlFor='startDate'>Data inizio</label>
                                     {/*Data inizio */}
                                    <input id='startDate' className={"form-control"} type='date' name='startDate' defaultValue={moment().add(1,'days').format("yyyy-MM-DD")}
                                    onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}/>
                                </div>
                                <div className="col-sm">
                                    <label htmlFor='endDate'>Data fine</label>
                                     {/*Data fine */}
                                    <input id='endDate' className={"form-control"} type='date' name='endDate' defaultValue={moment().add(3,'days').format("yyyy-MM-DD")} 
                                    onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}/>
                            </div>
                                
                            </div>
                            <div className="row" style={{"margin-top":"5%"}}>
                                <div className="col-sm">
                                    <label htmlFor='selectCategory'>Categoria</label>
                                     {/* Categoria*/}
                                    <select id='selectCategory' className={"form-control custom-select"} name='selectCategory' defaultValue={"A"}
                                    onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}>
                                        <option value="A">A</option>
                                        <option value="B">B</option>
                                        <option value="C">C</option>
                                        <option value="D">D</option>
                                        <option value="E">E</option>
                                    </select>

                                </div>
                                <div className="col-sm">
                                    <label htmlFor='eta'>anni guidatore</label>
                                     {/*Eta guidatore */}
                                    <select id='eta'className={"form-control custom-select"}  name='eta' defaultValue='1'
                                            onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}>
                                            <option value="1">meno di 25</option>
                                            <option value="2">tra 25 e 65</option>
                                            <option value="3">più di 65</option>
                                    </select>

                                </div>
                                <div className="col-sm">
                                    <label htmlFor='selectGuidatori'>Guidatori</label>
                                     {/*numero guidatori */}
                                    <select id='selectGuidatori' className={"form-control custom-select"} name='selectGuidatori' defaultValue={'0'}
                                    onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}>
                                        <option value='0'>0</option>
                                        <option value='1'>1</option>
                                        <option value='2'>2</option>
                                        <option value='3'>3</option>
                                        <option value='4'>4</option>
                                    </select>

                                </div>
                            </div>
                            <div className="row" style={{"margin-top":"5%"}}>
                                <div className="col-sm">
                                    <div className="custom-control custom-checkbox form-check">
                                         {/*Assicurazione */}
                                    <input type="checkbox" className= "custom-control-input checked" id={"check-ins"}   onChange={this.toggle} />
                                    <label className="custom-control-label" htmlFor={"check-ins"}>Assicurazione</label>
                                    </div>
                                </div>
                                <div className="col-sm">
                                        <label htmlFor='km'>Kilometri Gionalieri</label>
                                         {/*Kilometri giornalieri */}
                                        <select id='km'className={"form-control custom-select"}  name='km' defaultValue='1'
                                            onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}>
                                            <option value="1">meno di 50km</option>
                                            <option value="2">tra 50km e 150km</option>
                                            <option value="3">più di 50km</option>
                                        </select>
                                        
                                </div>
                                
                            </div>
                        

                        </div>
                    
                        <div className="container" >
                            <div style={{"width":"40%"}}>
                            <div className='row' >
                                <div className="card" style={{"width":"234px"}}>
                                    <div className="card-body">
                                         {/*Numero auto + prezzo */}
                                        <p>Auto presenti: {this.state.carCount}</p>
                                        <p>Prezzo : {this.state.price}€ </p>
                                    </div>
                                </div>
                            </div>

                            <div className="row " style={{"margin-top":"49%"}}>
                                 {/* Pulsante prenotazione*/}
                                <button style={{"width":"234px"}} type='button' className='btn btn-primary' disabled={this.state.APIerror || this.state.dateError || this.state.carCount===0? true :false} onClick={this.submitRequest}>Prenota</button>
                            </div>
                            </div>
                        </div>
                   
                    </div>
                    <div className={'form-row p-2'} style={{"width":"110%"}}>
                         {
                             (this.state.dateError===true)?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">Impossibile inserire queste date</div>): <div></div>
                         }
                     </div>
                     <div className={'form-row p-2'} style={{"width":"110%"}}>
                         {
                             (this.state.APIerror===true)?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">Problema di comunicazione col server</div>): <div></div>
                         }
                     </div>
                     <div className={'form-row p-2'} style={{"width":"110%"}}>
                         {
                             (this.state.APIerror===false &&  this.state.dateError===false && this.state.carCount===0)?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">Nessuna auto disponibile</div>): <div></div>
                         }
                     </div>
                </form>
            </div>) :
                
                (<div className='d-flex justify-content-center ' style={{"margin-top":"100px"}}>
                 
                    <form className='' method={'POST'} onSubmit={this.validateForm} ref={form=>this.form=form}>
                        <div className={'form-row '}>
                            <h3>Dati di pagamento</h3>
                            <div style={{"width":"100%"}} className={'form-group'}>
                                <label htmlFor='cardnumber'>Credit Card Number</label>
                                 {/* Carta di credito*/}
                                <input   id='cardnumber' className={'form-control'} type='text'required={true}
                                name='cardnumber' onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)} />
                            </div>
                            &nbsp;
                        </div>
                        <div className={'form-row '}>
                            <div style={{"width":"100%"}} className={'form-group'}>
                                 {/* nome completo*/}
                                <label htmlFor='completename'>Nome completo</label>
                                <input   id='completename' className={'form-control'} type='text'required={true}
                                name='completename' onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}/>
                            </div>
                            &nbsp;
                        </div>
                        <div className={'form-row '}>
                            <div style={{"width":"100%"}} className={'form-group'}>
                                <label htmlFor='ccv'>CCV</label>
                                 {/*CCV */}
                                <input   id='ccv' className={'form-control'} type='text'  required={true}
                                name='ccv' onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}/>
                            </div>
                            &nbsp;
                        </div>
                        <div className={'form-row'}>
                            <div className="container">
                                <div className="row">
                                    <div className="col-sm">
                                         {/* pulsante annulla*/}
                                        <button style={{"width":"100%"}} type='button' className='btn btn-primary' onClick={this.cancelRequest}>Annulla</button>
                                    </div>
                                    <div className="col-sm">
                                         {/* pulsante conferma*/}
                                        <button style={{"width":"100%"}} type='button' className='btn btn-primary' onClick={this.validatePayment}>Conferma</button>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div className={'form-row p-2'} style={{"width":"100%"}} >
                         
                             {(this.state.CardError==="all")?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">Inserisci tutti i dati correttamente</div>): <div></div>}
                             {(this.state.CardError==="card")?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">Numero di carta errato</div>): <div></div>}
                             {(this.state.CardError==="ccv")?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">CCV errato</div>): <div></div>}
                             {(this.state.CardError==="name")?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">inserisci il nome completo</div>): <div></div>}
                             {(this.state.CardError==="server")?(<div className="alert alert-danger"  style={{"margin-top":"30px","width":"100%"}} role="alert">Errore server</div>): <div></div>}
                        </div>
                    </form>

                    <div className="card" style={{"width":"200px", "margin-left":"20px"}} >
                         {/* Riepilogo prenotazione*/}
                       { this.state.prenotazione && <div className="card-body" >
                            <h3>Riepilogo</h3>
                            <p>Id auto: {this.state.prenotazione.carid}</p>           
                            <p>Modello: {this.state.prenotazione.modello}</p>
                            <p>Marca: {this.state.prenotazione.marca}</p>
                            <p>Categoria: {this.state.prenotazione.categoria}</p>
                            <p>Dal : {this.state.startDate}</p>
                            <p>Al : {this.state.endDate}</p>
                            <p>Prezzo : {this.state.prenotazione.price}€ </p>
                        </div>}
                    </div>
                </div>)
            }
            </>
        }
}

export default BookCarForm;