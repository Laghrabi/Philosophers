# Philosophers 🍽️

![Dining Philosophers Problem](https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png)

---

## 📖 Project Description  
The **Philosophers** project is an implementation of the classic **Dining Philosophers problem**, a synchronization challenge where multiple threads (philosophers) compete for shared resources (forks) without deadlocks or starvation.  

Key behaviors:  
- Philosophers alternate between **thinking**, **eating**, and **sleeping**.  
- Each needs **two forks** to eat (shared resources with neighbors).  
- The solution avoids **deadlocks** (e.g., circular waits) and ensures fairness.  

---

## ⚙️ Parameters  
The program accepts these arguments in order:  

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_meals>]