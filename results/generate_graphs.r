a_star = read.csv('a_star.csv')
a_star$alg = 'A*'
bfs = read.csv('bfs.csv')
bfs$alg = 'BFS'
ida = read.csv('ida_star.csv')
ida$alg = 'IDA*'
tot = rbind(a_star, ida, bfs)
tot[tot==-1] = NA

library(ggplot2)
library(scales)

ggplot(tot, aes(x = RunningTime..in.ns./1e9, color = alg)) + 
  stat_ecdf() +
  xlab("Running Time (seconds)") +
  ylab("") +
  scale_color_discrete("") +
  scale_y_continuous(labels = percent) +
  theme_grey() +
  theme(panel.background = element_blank())
ggsave("runtime.png")

ggplot(tot, aes(x = X.States, color = alg)) + 
  stat_ecdf() +
  xlab("States Expanded") +
  ylab("") + 
  scale_color_discrete("") +
  scale_y_continuous(labels = percent) +
  theme_grey() +
  theme(panel.background = element_blank())
ggsave("states.png")
