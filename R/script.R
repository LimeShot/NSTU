data <- read.table("D:\\NSTU\\R\\вариант-8(л.р.1).csv", header=TRUE, sep=";")

View(data)

colnames(data)[5] <- "кол.во.покупок"
colnames(data)[6] <- "ср.стоим.покупок"
colnames(data)[7] <- "ср.число.стр"
colnames(data)[8] <- "обращ.в.подд."
colnames(data)[9] <- "участие.в.опросах"
colnames(data)[10] <- "степень.удов.баллы"
colnames(data)[11] <- "степень.удов.кач"

View(data)

View(subset(data, data$возраст > 30))

View(subset(data, data$возраст < 30))

dataup30 = subset(data, data$возраст > 30)

datadown30 = subset(data, data$возраст < 30)

str(data)

quantitative_colls = c(4,5,6,7,8,10)

summary(data[quantitative_colls])

find_mode <- function(v) {
  uniqv <- unique(v)  
  uniqv[which.max(tabulate(match(v, uniqv)))]
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


apply(data[quantitative_colls], 2, mystats)

apply(dataup30[quantitative_colls], 2, mystats)

apply(datadown30[quantitative_colls], 2, mystats)

str(data)

plot(
  x = data$возраст,
  y = data$ср.стоим.покупок,
  main = "Диаграмма рассеяния",
  xlab = "Возраст",
  ylab = "Средняя стоимость покупок"
)


library(ggplot2)

# Построение радиальной диаграммы
freq_table <- table(data$степень.удов.кач)
df_summary <- as.data.frame(freq_table)
names(df_summary) <- c("category", "Freq")

ggplot(df_summary, aes(x = category, y = Freq, fill = category)) +
  geom_col(width = 1, color = "black") +
  coord_polar(theta = "x") +
  theme_minimal() +
  labs(x = NULL, y = "Частота", fill = "Категория") +
  theme(axis.text.x = element_text(size = 12))

# Построение категориальной радиальной диаграммы
df_summary <- as.data.frame(table(data$пол, data$группа))
names(df_summary) <- c("пол", "группа", "n")

ggplot(df_summary, aes(x = группа, y = n, fill = пол)) +
  geom_col(width = 1, colour = "gray90") +
  coord_polar() +
  scale_fill_manual(values = c("1" = "lightblue",    
                               "2" = "pink"),   
                    name = "Пол") +
  theme_minimal() +
  labs(title = "Категориальная радиальная диаграмма",
       fill = "Пол",
       x = "Группа", y = NULL)

# Построение столбиковой диаграммы
agg_data <- tapply(data$ср.стоим.покупок, list(data$группа, data$пол), mean)

barplot(agg_data, beside = TRUE,
        col = c("lightblue", "pink"),
        legend.text = TRUE,
        args.legend = list(title = "Пол"),
        xlab = "Группа",
        ylab = "Средняя стоимость покупок",
        main = "Столбиковая диаграмма по группе и полу")


# Ящик с усами
boxplot(data$кол.во.покупок ~ data$пол, 
        main="Диаграмма размаха для количества покупок", 
        ylab="Кол-во покупок", 
        xlab="Пол",
        col=c("lightblue", "pink"))

df_numeric <- data[quantitative_colls]
n <- ncol(df_numeric)
par(mfrow = c(2, 3))

# Рисуем гистограммы
for(i in 1:n) {
  hist(df_numeric[[i]], 
       main = names(df_numeric)[i],
       xlab = names(df_numeric)[i],
       col = "steelblue",
       border = "white")
}


library(GGally)

ggpairs(data, columns = quantitative_colls)

install.packages("nortest")
library(nortest)

shapiro.test(data$кол.во.покупок)

cvm.test(data$кол.во.покупок)

ad.test(data$кол.во.покупок)


str(data)

data_col1 <- data[data$возраст < 30, c(3, 9, 11)]
data_col2 <- data[data$возраст > 30, c(3, 9, 11)]

table11 = table(data_col1$пол,data_col1$участие.в.опросах)
table12 = table(data_col1$пол,data_col1$степень.удов.кач)
table13 = table(data_col1$участие.в.опросах,data_col1$степень.удов.кач)
table21 = table(data_col2$пол,data_col2$участие.в.опросах)
table22 = table(data_col2$пол,data_col2$степень.удов.кач)
table23 = table(data_col2$участие.в.опросах,data_col2$степень.удов.кач)
  
chisq.test(table11)
fisher.test(table11)

chisq.test(table12)
fisher.test(table12)

chisq.test(table13)
fisher.test(table13)

chisq.test(table21)
fisher.test(table21)

chisq.test(table22)
fisher.test(table22)

chisq.test(table23)
fisher.test(table23)

qualitative_coll <- "участие.в.опросах"

quantitative_colls <- names(data[quantitative_colls])

for (var in quantitative_colls){
  cat("\nПеременная", var, "\n")

  model <- aov(data[[var]] ~ data[[qualitative_coll]])
  print(summary(model))

  print(kruskal.test(data[[var]] ~ data[[qualitative_coll]]))
}

cor_dup <- cor(dataup30[, quantitative_colls], method = "pearson")
cor_dus <- cor(dataup30[, quantitative_colls], method = "spearman")
cor_duk <- cor(dataup30[, quantitative_colls], method = "kendall")
cor_downp <- cor(datadown30[, quantitative_colls], method = "pearson")
cor_downs <- cor(datadown30[, quantitative_colls], method = "spearman")
cor_downk <- cor(datadown30[, quantitative_colls], method = "kendall")

str(data)

install.packages("ggm")
library(ggm)
pcor(c(4,6,1,2,3,5),cov(dataup30[, quantitative_colls]))
pcor(c(4,6,1,2,3,5),cov(datadown30[, quantitative_colls]))

install.packages("corrplot")
library(corrplot)

par(mfrow = c(1, 1))

col <- colorRampPalette(c("#BB4444", "#EE9988", "#FFFFFF", "#77AADD",
                          "#4477AA"))
corrplot(cor_dus, method="color", col=NULL,
         type="upper", order="hclust",
         addCoef.col = "black", tl.col="black", tl.srt=45,
         sig.level = 0.01, insig = "blank",
         diag=FALSE
)
