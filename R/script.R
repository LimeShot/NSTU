data <- read.table("F:\\NSTU\\R\\вариант-8(л.р.1).csv", header=TRUE, sep=";")

colnames(data)[6] <- "процентр_успешных_задач"
colnames(data)[7] <- "количество_ошибок"
colnames(data)[8] <- "удовлетворенность_вбаллах"
colnames(data)[9] <- "удовлетворенность_качественная"
colnames(data)[10] <- "документирование"

View(data)

View(subset(data, data$возраст > 30))

View(subset(data, data$возраст < 30))

dataup30 = subset(data, data$возраст > 30)

datadown30 = subset(data, data$возраст < 30)

str(data)

summary(data)

find_mode <- function(v) {
  uniqv <- unique(v)                      # Находим уникальные значения
  uniqv[which.max(tabulate(match(v, uniqv)))]  # Возвращаем значение с максимальной частотой
}



mystats <- function(x)
{
  if(is.numeric(x)){
  minim <- min(x)
  maxim <- max(x)
  m <- mean(x)
  med <- median(x)
  mode <- find_mode(x)
  n <- length(x)
  s <- sd(x)
  quant <- quantile(x, c(.25, .75))
  asim <- sum((x-m)^3/s^3)/n
  ekcess <- sum((x-m)^4/s^4)/n - 3
  return(c(миниммум=minim, максимум=maxim, 
           среднее=m,стандартное.отклонение=s, 
           квартиль=quant,
           медиана=med,
           мода=mode,
           коэффициент.асимметрии=asim,
           коэффициент.эксцесса=ekcess))}
}


apply(data[1:3], 2, mystats)
apply(data[4:6], 2, mystats)
apply(data[7:9], 2, mystats)

apply(dataup30[1:3], 2, mystats)
apply(dataup30[4:6], 2, mystats)
apply(dataup30[7:9], 2, mystats)

apply(datadown30[1:3], 2, mystats)
apply(datadown30[4:6], 2, mystats)
apply(datadown30[7:9], 2, mystats)

str(data)

plot(
  x = data$возраст,
  y = data$средняя.стоимость..покупок.за.год,
  main = "Диаграмма рассеяния",
)

install.packages("fmsb")
library(fmsb)


boxplot(data$количество.покупок..за.год ~ data$группа, main="диаграмма размаха для покупок", ylab="кол-во покупок")

library(ggplot2)
library(GGally)

ggpairs(data, columns = 4:10)

install.packages("nortest")
library(nortest)

shapiro.test(data$количество.покупок..за.год)

cvm.test(data$количество.покупок..за.год)

ad.test(data$количество.покупок..за.год)


table<-table(data$name_1,data$name_2)

str(data)

data_col1 = data[data$группа==1,c(3,11)]
data_col2 = data[data$группа==2,c(3,11)]

table1 = table(data_col1$пол,data_col1$степень..удовлетворенности.услугами..качественная.оценка.)
table2 = table(data_col2$пол,data_col2$степень..удовлетворенности.услугами..качественная.оценка.)
  
chisq.test(table1)
fisher.test(table1)

chisq.test(table2)
fisher.test(table2)





