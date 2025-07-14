set terminal pngcairo size 800,600
set output "graphs/unique_visited_nodes_plot.png"

set datafile separator ","
set xlabel "Hops"
set ylabel "Uniquely visited nodes"
set title "Random Walker Network Coverage"
set grid
set key outside top right     # 🧭 Legend outside
set yrange [0:20]             # 📏 Lock Y-axis

set style line 1 lc rgb "#8f77b4" lw 2 pt 7 ps 1.2
set style fill solid

plot \
     "data/unique_visited_nodes.txt" using 1:2 with lines lw 2 lc rgb "#1f77b4" notitle, \
     "data/unique_visited_nodes.txt" every 10 using 1:2 with points pt 7 ps 1.2 lc rgb "#1f77b4" title "Sampled Points"

set output

