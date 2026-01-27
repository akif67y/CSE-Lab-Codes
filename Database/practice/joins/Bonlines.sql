select e1.employee_id, e1.last_name
from employees e1 
join departments d1 on
 (e1.employee_id = d1.manager_id ) 
 join locations l on (l.location_id = d1.location_id)
where l.city in ('Toronto', 'Oxford') and (select avg(e2.salary)
                                            from employees e2
                                            where e2.department_id = d1.department_id ) > (select avg(e2.salary)
                                            from employees e2
                                             );

 SELECT e1.employee_id
 from employees e1
 where (select count(e2.employee_id)
        from employees e2
        where e2.department_id = e1.department_id) > 5 and e1.salary > (select avg(e3.salary)
                                                            from employees e3);

SELECT e1.first_name || ' '|| e1.last_name full_name, e1.salary, d1.department_name, case 
                                                                                        when e1.salary > 1.7 * (select avg(e4.salary)
from employees e4
where e4.department_id = e1.department_id) then 'Stable High Earner'
else 'Dept Above Avg' end Label
from employees e1 join departments d1 on (e1.department_id= d1.department_id) 
where d1.manager_id is not null and e1.salary > (select avg(e3.salary)
from employees e3
where e3.department_id = e1.department_id) and not exists(select jh.employee_id
from job_history jh
where jh.employee_id = e1.employee_id);       

select e1.employee_id, e1.first_name, e1.last_name, e1.department_id, e1.job_id, e1.salary
from employees e1
where (((select count(e2.employee_id)
from employees e2
where e2.department_id = e1.department_id )) > 5 or ((select min(e3.salary)
from employees e3
where e3.job_id = e1.job_id) > 10000));

select e1.employee_id, e1.first_name, e1.last_name, e1.department_id, e1.job_id, e1.salary
from employees e1
where (((select count(e2.employee_id)
from employees e2
where e2.department_id = e1.department_id )) > 5 or ((select min(e3.salary)
from employees e3
where e3.job_id = e1.job_id) > 10000)) and not (((select count(e2.employee_id)
from employees e2
where e2.department_id = e1.department_id )) > 5 and ((select min(e3.salary)
from employees e3
where e3.job_id = e1.job_id) > 10000)) ;



((select e1.employee_id, e1.first_name, e1.last_name, e1.department_id, e1.job_id, e1.salary
from employees e1
where ((select count(e2.employee_id)
from employees e2
where e2.department_id = e1.department_id )) > 5) union (select e1.employee_id, e1.first_name, e1.last_name, e1.department_id, e1.job_id, e1.salary
from employees e1 
where ((select min(e3.salary)
from employees e3
where e3.job_id = e1.job_id) > 10000))) minus ((select e1.employee_id, e1.first_name, e1.last_name, e1.department_id, e1.job_id, e1.salary
from employees e1
where ((select count(e2.employee_id)
from employees e2
where e2.department_id = e1.department_id )) > 5) intersect (select e1.employee_id, e1.first_name, e1.last_name, e1.department_id, e1.job_id, e1.salary
from employees e1 
where ((select min(e3.salary)
from employees e3
where e3.job_id = e1.job_id) > 10000)));


--solution : 
SELECT 
    m.employee_id, 
    m.first_name, 
    m.last_name, 
    d.department_name
FROM employees m
JOIN departments d ON m.employee_id = d.manager_id
JOIN locations l ON d.location_id = l.location_id
JOIN employees e ON d.department_id = e.department_id
WHERE l.city IN ('Toronto', 'Oxford')
GROUP BY m.employee_id, m.first_name, m.last_name, d.department_name
HAVING AVG(e.salary) > (SELECT AVG(salary) FROM employees);

select e1.employee_id, e1.last_name
from employees e1 
join departments d1 on
 (e1.employee_id = d1.manager_id ) 
 join locations l on (l.location_id = d1.location_id)
where l.city in ('Toronto', 'Oxford') and (select avg(e2.salary)
                                            from employees e2
                                            where e2.department_id = d1.department_id ) > (select avg(e2.salary)
                                            from employees e2
                                             );

SELECT 
    e.employee_id, 
    e.first_name, 
    e.last_name, 
    e.salary, 
    e.department_id
FROM employees e
WHERE e.department_id IN (
    SELECT department_id 
    FROM employees 
    GROUP BY department_id 
    HAVING COUNT(*) > 5
)
AND e.salary > (SELECT AVG(salary) FROM employees);

SELECT 
    e.first_name || ' ' || e.last_name AS full_name,
    e.salary,
    d.department_name,
    CASE 
        WHEN e.salary > 1.7 * da.avg_dept_salary THEN 'Stable High Earner'
        ELSE 'Dept Above Avg'
    END AS salary_label
FROM employees e
JOIN departments d ON e.department_id = d.department_id
JOIN (
    SELECT department_id, AVG(salary) AS avg_dept_salary 
    FROM employees 
    GROUP BY department_id
) da ON e.department_id = da.department_id
WHERE d.manager_id IS NOT NULL
  AND e.employee_id NOT IN (SELECT employee_id FROM job_history)
  AND e.salary > da.avg_dept_salary;

SELECT 
    e.employee_id, 
    e.first_name, 
    e.last_name, 
    e.department_id, 
    e.job_id, 
    e.salary
FROM employees e
JOIN jobs j ON e.job_id = j.job_id
WHERE e.department_id IN (
    SELECT department_id 
    FROM employees 
    GROUP BY department_id 
    HAVING COUNT(*) > 5
)
OR j.min_salary > 10000;

WITH Dept_Counts AS (
    SELECT department_id, COUNT(*) as emp_count
    FROM employees
    GROUP BY department_id
)
SELECT 
    e.employee_id, 
    e.first_name || ' ' || e.last_name AS full_name, 
    e.department_id, 
    e.job_id, 
    e.salary
FROM employees e
JOIN jobs j ON e.job_id = j.job_id
LEFT JOIN Dept_Counts dc ON e.department_id = dc.department_id
WHERE 
    (COALESCE(dc.emp_count, 0) > 5 AND j.min_salary <= 10000)
    OR 
    (COALESCE(dc.emp_count, 0) <= 5 AND j.min_salary > 10000);







                                                                 