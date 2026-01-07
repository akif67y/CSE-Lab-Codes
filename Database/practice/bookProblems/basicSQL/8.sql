select first_name || ' ' || last_name last_name
from employees
where job_id = 'AD_PRES' and salary >= 23000