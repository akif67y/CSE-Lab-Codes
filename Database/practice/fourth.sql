select department_id, job_id, min(hire_date) minimum_hire_date, max(hire_date) maximum_hire_date, round(avg(salary),2) Salary_avg
from EMPLOYEES
where department_id is not null and JOB_ID is not null
group by DEPARTMENT_ID, JOB_ID
having avg(salary) >8000


