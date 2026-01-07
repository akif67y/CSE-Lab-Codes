select job_id,max(salary), min(salary), avg(salary)
from EMPLOYEES
group by job_id;

select department_id, count(*) total
from EMPLOYEES
group by DEPARTMENT_ID;

select job_id, job_title, count(*) total
from JOBS
group by job_id, job_title;

select  salary, count(*)
from EMPLOYEES
group by salary;
