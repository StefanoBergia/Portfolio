import React from 'react';
import './App.css';
import NavBar from './NavBar'
import CarSelector from './CarSelector';
import LoginForm from './LoginForm';
import {Route,Switch,Redirect,withRouter} from 'react-router-dom'
import API from './API'
import BookCarForm from './BookCarForm';
import RentHistory from './RentHistory';

class App extends React.Component{

  constructor(){
    super();
    this.state={ authErr:null, authUser:null};
    this.resetUser=this.resetUser.bind(this);
  }

  componentDidMount(){
    //veririfico se esiste un token e recupero l'utente loggato
    API.getLoggeduser().then((ret)=>this.setState({authUser:ret.username}))
    .catch((err)=>{console.log("no logged user")});
  }

  login=(username,password,booking)=>{
    API.userLogin(username,password)
    .then((user)=>{
      this.setState({authUser:user.username,authErr:null});
      //booking è un flag che mi dice se devo essere reinderizzato a / o /prenota
      if(!booking)
        this.props.history.push("/");
      else
        this.props.history.push("/prenota");
    })
    .catch((err)=>{ 
      if(err && err!=={}){
        this.setState({authErr:err});
        if(!booking)
        this.props.history.push("/login");
      else
        this.props.history.push("/login/prenota");
    }
    });
  }

  logout=()=>{
    if(this.state.authUser!==null){
      API.userLogout().then(
        ()=>{
          this.setState({authUser:null,authErr:null});
        }
      );
    }
  }

  //funzioni per gestire il reindirizzamento da altre pagine
  goToPersonalPage=()=>{
    this.props.history.push("/storico");
  }

  goToMainPage=()=>{
    this.props.history.push("/");
  }

  goToReservation=()=>{
    this.props.history.push("/prenota");
  }

  resetUser=()=>{
    this.setState({authUser:null,authErr:null});
  }

  //questa funzione ritorna true se un cookie 'c_name' esiste
  getCookie= function(c_name) {
    console.log(c_name);
      let c_value = document.cookie,
          c_start = c_value.indexOf(" " + c_name + "=");
      if (c_start === -1) 
          c_start = c_value.indexOf(c_name + "=");
      if (c_start === -1) {
          c_value = null;
      } else {
          c_start = c_value.indexOf("=", c_start) + 1;
          let c_end = c_value.indexOf(";", c_start);
          if (c_end === -1) {
              c_end = c_value.length;
          }
          c_value = unescape(c_value.substring(c_start, c_end));
      }
      return c_value;
  }

  render(){
       return (
       <>
        <NavBar user={this.state.authUser} logout={this.logout}/>
        
        <Switch>
      
        <Route path='/login/prenota' render={(props)=>{
             return <>
             {
             //form di login con redirect alla pagina di prenotazione
             !this.state.authUser?
            <LoginForm getLoggeduser={API.getLoggeduser} 
                        goToPersonalPage={this.goToPersonalPage} 
                        goToMainPage={this.goToMainPage} 
                        goToReservation={this.goToReservation}
                        prenota={true} 
                        storico={false}
                        userLogin={this.login} 
                        err={this.state.authErr===null?false:true} />
              : <Redirect to='/prenota' />
              }</>
          
           }}/>

            <Route path='/login/storico' render={(props)=>{
             return <>
             {
             //form di login con redirect alla pagina di storico
             !this.state.authUser?
             <LoginForm getLoggeduser={API.getLoggeduser} 
                        goToPersonalPage={this.goToPersonalPage} 
                        goToMainPage={this.goToMainPage} 
                        goToReservation={this.goToReservation}
                        prenota={false} 
                        storico={true}
                        userLogin={this.login} 
                        err={this.state.authErr===null?false:true} />
              : <Redirect to='/storico' />
              }</>
          
           }}/>
           <Route path='/login' render={(props)=>{
             return <>
             {/*form di login standard*/} 
             <LoginForm getLoggeduser={API.getLoggeduser} 
                        goToPersonalPage={this.goToPersonalPage} 
                        goToMainPage={this.goToMainPage} 
                        goToReservation={this.goToReservation}
                        prenota={false} 
                        storico={false}
                        userLogin={this.login} 
                        err={this.state.authErr==null?false:true}/>
             </>
           }}/>
          
           <Route path='/prenota' render={(props)=>{
             return <>
             <BookCarForm user={this.state.authUser} 
                          getNumberandPrice={API.getNumberandPrice} 
                          submitRequest={API.submitRequest} 
                          confirmPayment={API.confirmPayment}
                          deleteRequest={API.deleteRequest}
                          done={this.goToPersonalPage}
                          getCookie={this.getCookie}
                          resetUser={this.resetUser}/>
            </>
           }}/>
             <Route path='/storico' render={(props)=>{
                return <RentHistory authUser={this.state.authUser} 
                        getCookie={this.getCookie} 
                        getRentList={API.getRentHistory} 
                        deleteRent={API.deleteRequest}
                        resetUser={this.resetUser}/>
             }}/>
        
            <Route path='/' render={(props)=>{
              return <>
              <h2 style={{"margin-top":"100px","margin-left":"70px"}}>
              {this.state.authUser===null? "Benvenuto":"Benvenuto "+this.state.authUser}
            </h2>
              <CarSelector getCarList={API.getCarList}/>
              </>
            }}/>


          </Switch>
        </>
       ); 
  }
}

export default withRouter(App);
