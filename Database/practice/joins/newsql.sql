select e.employee_id, e.hire_date, e.department_id, jh.start_date, jh.end_date, jh.department_id
from employees e left outer join job_history jh on (e.employee_id = jh.employee_id)
where e.job_id = jh.job_id;