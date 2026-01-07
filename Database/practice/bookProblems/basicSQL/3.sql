select first_name || ' ' || last_name name
from employees
where hire_date < '01-JAN-1998'