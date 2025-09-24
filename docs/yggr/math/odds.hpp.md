---
GitHub Copilot: odds.hpp 文档

---

# odds.hpp

## 简介

该头文件实现了赔率（Odds）、胜率（Winning）、失败率（Failure Rate）等概率相关的转换工具，支持浮点型和整型赔率的互转、概率计算等。适用于博彩、金融、风险评估等概率与赔率相关的场景。

## 主要内容

### 1. 赔率与浮动赔率互转

- `odds_to_floating_odds`：赔率转浮动赔率（如欧赔，$odds+1$）。
- `floating_odds_to_odds`：浮动赔率转赔率（$odds-1$）。

### 2. 赔率与胜率/失败率互转

- `odds_to_winning`：赔率转胜率，支持浮点和整型赔率。
- `odds_to_failure_rate`：赔率转失败率。
- `winning_to_odds` / `winning_to_floating_odds`：胜率转赔率/浮动赔率。
- `failure_rate_to_odds` / `failure_rate_to_floating_odds`：失败率转赔率/浮动赔率。

### 3. 其它概率工具

- `single_lose_odds`：单次失败赔率。
- `limit_continuous_lose_count`：给定游戏次数和赔率，计算极限连续失败次数。

### 4. 依赖关系

- 依赖 Boost 类型萃取、断言、cmath 等。

## 典型用途

- 博彩、金融、风险评估等概率与赔率相关的计算。
- 支持浮点和整型赔率，适合多种业务场景。

---



