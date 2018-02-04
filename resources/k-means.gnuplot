set angles degrees
set terminal gif animate delay 5 loop 0 optimize
set output "rot3.gif"

n =100 
splot "mnms.data" with points pointtype 12
do for [i=1:n] {
   set view 60, i*360/n
   replot
}