select last_name, round(sysdate-hire_date,2)
from EMPLOYEES;

select last_name, trunc((sysdate-hire_date)/365,3) "Years Served"
from EMPLOYEES;

select last_name,  ADD_MONTHS(trunc(hire_date, 'MONTH'),1) - hire_date "days worked" 
from EMPLOYEES;

select commission_pct 
from EMPLOYEES
where nvl(COMMISSION_PCT, 1) < 0.2;

select nvl(salary,0) * (5 * 12 + 6) "total salary"
from employees;

select last_name, to_char(hire_date, 'ddth Month,YYYY') Hiing
from employees;

select last_name, to_char(hire_date, 'dd Month,YYYY') Hiing
from employees;
