/******************************************************************************
* jslib_llnl01.js
*
* This library includes code that implements web page menus, footers, and other
* functions.
*
* Blaise M. Barney  blaiseb@llnl.gov
* Last revised: 02/06/2002
*******************************************************************************/

/******************************************************************************
* These section implements the mouse-over menu images 
*******************************************************************************/
  var menuOff_home = new Image();
  menuOff_home.src = "../images/menuOff_home.gif";
  var menuOn_home = new Image();
  menuOn_home.src = "../images/menuOn_home.gif";

  var menuOff_agenda = new Image();
  menuOff_agenda.src = "../images/menuOff_agenda.gif";
  var menuOn_agenda = new Image();
  menuOn_agenda.src = "../images/menuOn_agenda.gif";

  var menuOff_tutorials = new Image();
  menuOff_tutorials.src = "../images/menuOff_tutorials.gif";
  var menuOn_tutorials = new Image();
  menuOn_tutorials.src = "../images/menuOn_tutorials.gif";

  var menuOff_exercises = new Image();
  menuOff_exercises.src = "../images/menuOff_exercises.gif";
  var menuOn_exercises = new Image();
  menuOn_exercises.src = "../images/menuOn_exercises.gif";

  var menuOff_abstracts = new Image();
  menuOff_abstracts.src = "../images/menuOff_abstracts.gif";
  var menuOn_abstracts = new Image();
  menuOn_abstracts.src = "../images/menuOn_abstracts.gif";

function act(imgName) {
  document[imgName].src = eval("menuOn_" + imgName + ".src");
}

function inact(imgName) {
  document[imgName].src = eval("menuOff_" + imgName + ".src"); 
}

/******************************************************************************
* These section includes miscellaneous functions that are self explanatory.
* Some may not be used but may come in handy in the future.  
*******************************************************************************/
function PrintFooter() {
  document.write("<P><HR><DIV CLASS=footer>");
  document.write(document.location,"<BR>");
  document.write("Last Modified: ",document.lastModified," ");
  document.write("<A HREF=mailto:blaiseb@llnl.gov>blaiseb@llnl.gov</A>");
  document.write("<BR>UCRL-MI-133316</DIV><P>");
  defaultStatus = document.location;
  }

function go_to(x) {
  if(top.window.navigation) {
    top.window.mainwindow.location = x.toc.options[x.toc.selectedIndex].value ; 
    document.tocform.reset();
    }
  }

function popUp(url) {
  HelperWindow=window.open('', '', 'toolbar=no,menubar=no,location=no,  \
    directories=no,status=no,scrollbars=yes,resizable=yes,copyhistory=no,  \
    width=600,height=400');
  HelperWindow.location=url;
  HelperWindow.focus();
  }                        

function openWindow(url) {
  var thedate, randomname;
  thedate = new Date();
  randomname = thedate.getTime();
  NewWindow= window.open(url,randomname,'toolbar=yes,location=no,directories=no,status=no,scrollbars=yes,resizable=yes, copyhistory=no,width=600,height=400')
  }  

function resetTop(url) {
  document.write();
  top.location=url;
  }

function Answers(code) {
  if (code == 'pthreads01') {
    confirm ("ANSWER: \
    It is up to the implementation and/or operating system to decide where \
    and when threads will execute.  Robust programs should not depend upon \
    threads executing in a specific order.")
    }
  else if (code == 'pthreads02') {
    confirm ("ANSWER: \
    Make sure that all passed data is thread safe - that it can not be \
    changed by other threads.  The three examples that follow demonstrate \
    what not and what to do.")
    }
  else if (code == 'pthreads03') {
    confirm ("ANSWER: \
    Unless thread priority scheduling (not covered) is used, the \
    assignment will be left to the native system scheduler and may appear to \
    be more or less random.")
    }

  if (code == 'openMP01') {
    confirm ("ANSWER: \
    If there are more threads than sections, some threads will not \
    execute a section and some will.  If there are more sections than \
    threads, the implementation defines how the extra sections are \
    executed.")
    }
  else if (code == 'openMP02') {
    confirm ("ANSWER: \
    It is up to the implementation to decide which threads will execute \
    a section and which threads won't, and it can vary from execution \
    to execution.")
    }
  else if (code == 'openMP03') {
    confirm ("ANSWER: \
    For both examples, alpha[3] should equal 3, and beta[3] is \
    undefined or zero.  This is because only THREADPRIVATE variables \
    can persist between successive parallel regions.")
    }
  }  

function addNavigation() {
 if(!top.window.navigation) {
    document.write(" \
    <table border=0><tr align=center valign=center>  \
    <td><font size=-1 face=arial>  \
    <a href=../index.html>Home</a></b></font></td>  \
    <td><b>|</b></td> \
    <td><font size=-1 face=arial>  \
    <a href=../agenda/index.html>Agenda</a></b></font></td>  \
    <td><b>|</b></td> \
    <td><font size=-1 face=arial>  \
    <a href=../tutorials/index.html>Tutorials</a></b></font></td>  \
    <td><b>|</b></td> \
    <td><font size=-1 face=arial>  \
    <a href=../exercises/index.html>Exercises</a></b></font></td>  \
    <td><b>|</b></td> \
    <td><font size=-1 face=arial>  \
    <a href=../abstracts/index.html>Abstracts</a></b></font></td>  \
    <td><b>|</b></td> \
    <td><font size=-1 face=arial>  \
    <a href=http://www.llnl.gov/computing/training  \
      target=W2>LC&nbsp;Workshops</a></b></font></td>  \
    <td><b>|</b></td> \
    <td><font size=-1 face=arial>  \
    <a href=../misc/comments.html>Comments</a></b></font></td>  \
    <td><b>|</b></td> \
    <td><font size=-1 face=arial>  \
    <a href=../search/index.html>Search</a></font></td>  \
    </tr></table> \
    ");
    }
  document.write(" \
  <a href=http://www.llnl.gov/disclaimer.html target=W2><img \
  src=../images/privacyLegal.gif  width=107 height=20 border=0\
  alt='Privacy and Legal Notice'></a></font> \
  ");
  }
