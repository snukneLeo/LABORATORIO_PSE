#!/usr/bin/gnuplot

set terminal postscript eps enhanced color font 'Helvetica,10'
set output 'execution.eps'

set xrange [0:10]
set yrange [-1.5:1.5]

lower = -2
upper = 2

set key right bottom
set key font ",30"
set key spacing 4

reference = 'logs/reference.log'
plant = 'logs/execution.log'

set xlabel "Time (s)"
set ylabel "Values"

plot \
reference with line  linewidth 4  linetype rgb "#0000FF" title "Reference", \
plant with line linewidth 4 linetype rgb "#778899" title "Plant"


