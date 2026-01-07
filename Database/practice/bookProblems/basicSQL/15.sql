select last_name, salary, job_id
from employees
where last_name like '__a%' and job_id not like '%REP' and (department_id not in (90,100)) --last part ta not in diye kora jay
order by job_id asc, salary desc 