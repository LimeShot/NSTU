import pandas as pd
import re
from calendar import monthrange

from pathlib import Path

APP_DIR = Path(__file__).resolve().parent
DATA_FILE = APP_DIR / 'static' / 'data' / 'climate_17150.csv'
# Путь к CSV
df = pd.read_csv(DATA_FILE)

# Учитываем только пары "температура + осадки", где температура строго > 10.
temp_months = {
    int(match.group(1)): col
    for col in df.columns
    for match in [re.fullmatch(r"Tem(\d+)", col)]
    if match
}
osadki_months = {
    int(match.group(1)): col
    for col in df.columns
    for match in [re.fullmatch(r"Os(\d+)", col)]
    if match
}
paired_months = sorted(set(temp_months) & set(osadki_months))

df["tem_active"] = 0.0
df["sum_osadki"] = 0.0

for month in paired_months:
    temp_col = temp_months[month]
    os_col = osadki_months[month]

    days = df["year"].astype("Int64").apply(
        lambda y: monthrange(int(y), month)[1] if pd.notna(y) else pd.NA
    )

    valid_pair = df[temp_col].notna() & df[os_col].notna()
    active_period = valid_pair & (df[temp_col] > 10)

    df["tem_active"] += df[temp_col].where(active_period, 0) * days
    df["sum_osadki"] += df[os_col].where(active_period, 0)

# ГТК (если активных температур нет, возвращаем NaN)
gtk_raw = df["sum_osadki"] / (0.1 * df["tem_active"])
df["GTK"] = gtk_raw.round(2).where(df["tem_active"] > 0)

# Сохраняем новый файл
df.to_csv(DATA_FILE.parent / 'climatdata_GTK.csv', encoding='utf-8', index=False)

print("climatdata_GTK.csv создан!")
print(df[["year", "tem_active", "sum_osadki", "GTK"]].head())
