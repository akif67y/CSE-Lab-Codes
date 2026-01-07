select last_name, salary, commission_pct
from EMPLOYEES
where DEPARTMENT_ID = 80 and (( salary > 10000 and commission_pct < 0.2) or (salary < 7000 and commission_pct> 0.25)); -- 10,000 comma dile chod khabe