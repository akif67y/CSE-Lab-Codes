select manager_id
from EMPLOYEES
where employee_id is not NULL and manager_id is not null
group by manager_id
having count(*) > 5;

select employee_id
from employees
where to_char(hire_date, 'MM') = '04';

select job_id, count(*) "Count of >5000 employees"
from employees
where salary >= 5000
group by job_id;

select employee_id
from EMPLOYEES
where lower(email)  like '%gmail%';

select employee_id
from EMPLOYEES
where first_name like 'S%' and mod(salary, 2000) = 0;

select Upper(substr(last_name, length(last_name) , 1)) Last_Letter, count(*) Total
from EMPLOYEES
group by Upper(substr(last_name, length(last_name) , 1))
order by Last_Letter;

