set terminal pngcairo size 800,600
set output "graphs/merged_simulations_plot.png"

set datafile separator ","
set xlabel "Hops"
set ylabel "Uniquely visited nodes"
set title "Random Walker Network Coverage Comparison"
set grid
set key outside top right
set yrange [0:20]

# Define line styles
set style line 1 lc rgb "#1f77b4" lw 2
set style line 2 lc rgb "#ff7f0e" lw 2
set style line 3 lc rgb "#bf3b0e" lw 2

# --- Detect final point for each file ---
stats "data/unique_visited_nodes_1.txt" using 1:2 nooutput
x1 = STATS_max_x
y1 = STATS_max_y

stats "data/unique_visited_nodes_2.txt" using 1:2 nooutput
x2 = STATS_max_x
y2 = STATS_max_y

stats "data/unique_visited_nodes_3.txt" using 1:2 nooutput
x3 = STATS_max_x
y3 = STATS_max_y

# --- Draw guide lines for each final point ---
set arrow from x1, y1 to x1, 0 nohead lc rgb "gray" dt 2
set arrow from 0, y1 to x1+5, y1 nohead lc rgb "gray" dt 2
set label sprintf("End: (%d, %d)", x1, y1) at x1, y1+0.5 right

set arrow from x2, y2 to x2, 0 nohead lc rgb "gray" dt 2
set arrow from 0, y2 to x2+5, y2 nohead lc rgb "gray" dt 2
set label sprintf("End: (%d, %d)", x2, y2) at x2, y2+0.5 right

set arrow from x3, y3 to x3, 0 nohead lc rgb "gray" dt 2
set arrow from 0, y3 to x3+5, y3 nohead lc rgb "gray" dt 2
set label sprintf("End: (%d, %d)", x3, y3) at x3, y3+0.5 right

# --- Plot curves ---
plot \
     "data/unique_visited_nodes_1.txt" using 1:2 with lines linestyle 1 title "1 RW", \
     "data/unique_visited_nodes_2.txt" using 1:2 with lines linestyle 2 title "2 RW", \
     "data/unique_visited_nodes_3.txt" using 1:2 with lines linestyle 3 title "3 RW"

set output

