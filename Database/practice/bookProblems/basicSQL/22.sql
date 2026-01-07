select manager_id, count(*) total
from EMPLOYEES
group by manager_id;

select department_id, count(*) total
from employees
where salary >= 3000
group by department_id;



