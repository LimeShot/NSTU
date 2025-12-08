data <- read.table("~/NSTU/R/lab 1/вариант-8(л.р.1).csv", header = TRUE, sep = ";")

View(data)

colnames(data)[5] <- "кол_во.покупок"
colnames(data)[6] <- "ср.стоим.покупок"
colnames(data)[7] <- "ср.число.стр.за.визит"
colnames(data)[8] <- "кол-во.обр.в.сл.подд."
colnames(data)[9] <- "степень.удовл"
colnames(data)[10] <- "степень.актив"


View(data$кол_во.покупок[data$возраст > 30])

View(data$кол_во.покупок[data$возраст < 30])

str(data)

summary(data)
