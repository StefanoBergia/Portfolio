import React from 'react';

class LoginForm extends React.Component{
    constructor(props){
        super(props);
        //delay serve per la visualizzazione del messaggio di login errato
        this.state={username:'',password:'',delay:true};
    }

    componentDidMount(){
        //verifico se l'utente è già loggato e lo reindirizzo alla pagina da cui proviene
        this.props.getLoggeduser().then((ret)=>{
            if(ret.username){
                if(this.props.storico)
                    this.props.goToPersonalPage();
                else if(this.props.prenota)
                    this.props.goToReservation();
                else
                    this.props.goToMainPage();
            }
        }).catch((err)=>{console.log("no logged user")});
      }

    updateField=(name,value)=>{
        this.setState({[name]:value});
    }

    doLogin=(event)=>{
        event.preventDefault();
        this.setState({delay:false});
        //ritardo di 0.2s per visualizzazione messaggio di errore
        setTimeout(()=>{
            this.setState({delay:true});
        },200);
        if(this.form.checkValidity()){
            this.props.userLogin(this.state.username,this.state.password,this.props.prenota);
        }else{
            this.form.reportValidity();
        }
    }

    validateForm=(event)=>{
        event.preventDefault();
    }

    render(){
        
            return <div className='d-flex justify-content-center ' style={{"margin-top":"100px"}}>
               
                <form className='' method={'POST'}
                onSubmit={this.validateForm} ref={form=>this.form=form}>
                    
                    <div className={'form-row '}>
                        <div style={{"width":"100%"}} className={'form-group'}>
                            <label htmlFor='username'>Username</label>
                            {/*form username */}
                            <input   id='username' className={'form-control'} type='text'required={true}
                            name='username' value={this.state.username}
                            onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}
                            />
                        </div>
                        &nbsp;
                     </div>   
                     <div className={'form-row '}>
                        <div style={{"width":"100%"}} className={'form-group'}>
                            <label htmlFor='password'>Password</label>
                             {/*form password */}
                            <input   id='password' className={'form-control'} type='password'required={true}
                            name='password' value={this.state.password}
                            onChange={(ev)=>this.updateField(ev.target.name,ev.target.value)}
                            />
                        </div>
                        &nbsp;
                     </div> 
                     <div className={'form-row p-2'} style={{"width":"300px"}}>
                          {/*pulsante login */}
                         <button style={{"width":"100%"}} type='button' className='btn btn-primary' disabled={this.props.mode==='loginInProgress'} onClick={this.doLogin}>Login</button>
                     </div>
                     <div className={'form-row p-2'}>
                         {
                             (this.props.prenota===true || this.props.storico===true)?(<div className="alert alert-primary"  style={{"width":"100%"}} role="alert">Accedi per prenotare un veicolo</div>): <div></div>
                         }
                     </div>
                     <div className={'form-row p-2'}>
                         {
                             (this.props.err===true && this.state.delay)?(<div className="alert alert-danger" style={{"width":"100%"}} role="alert">Nome utente o password errati!</div>): <div></div>
                         }
                     </div>
                     <div className={'form-row p-2'}>
                         {
                             //(this.props.tokenExpired===true)?(<div className="alert alert-danger" style={{"width":"100%"}} role="alert">Token di accesso scaduto!</div>): <div></div>
                         }
                     </div>
                </form>
            </div>
    }
}

export default LoginForm;