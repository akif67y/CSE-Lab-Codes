select employee_id, first_name ||' '||last_name "Full Name", department_id, salary + salary * nvl(commission_pct,0) "Total Salary"
from EMPLOYEES
where first_name like 'D%' and last_name like '___n%' and DEPARTMENT_ID BETWEEN 20 and 70;

select job_id
from JOB_HISTORY
where (end_date - start_date) <= 1500
group by job_id
having count(*) >= 2;


select department_id, min(salary) MINIMUM_SALARY, max(salary) MAXIMUM_SALARY, round(avg(salary), 2) AVG_SALARY
from EMPLOYEES
where DEPARTMENT_ID <> 50
group by DEPARTMENT_ID
order by max(salary) - min(salary) desc, avg(salary) asc;

select manager_id, count(*) number_of_emplyees, avg(salary) AVG_SALARY
from EMPLOYEES
where MANAGER_ID is not null 
group by manager_id
having  avg(salary) < 4000 and count(*) < 10
order by count(*) asc, avg(salary) desc; 


select last_name
from employees 
where MOD(length(replace(replace(replace(replace(replace(lower(last_name), 'a', ''),'e', ''),'i', ''), 'o', ''),'u', '')),2) =1;
