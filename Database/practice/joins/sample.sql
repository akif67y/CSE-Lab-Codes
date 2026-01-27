select e.last_name, department_id, d.department_name
from employees e join departments d using(department_id);

select e1.last_name Manager_name, count(e2.employee_id) count_manages
from employees e1 left outer join employees e2 
on(e1.employee_id = e2.manager_id)
group by e1.employee_id, e1.last_name
order by e1.employee_id;

select e.last_name, e.salary, j.job_title
from employees e join jobs j on(e.job_id = j.job_id);

select d.DEPARTMENT_NAME, c.COUNTRY_NAME
from departments d join locations l on(d.location_id = l.location_id) join countries c on(c.country_id = l.country_id);

select c.country_name, count(d.department_id) department_count
from departments d join locations l on(d.location_id = l.location_id) right outer join countries c on(c.country_id = l.country_id)
group by c.country_id, c.country_name;

--SELECT employee_id, salary, count(*)
--from employees 
--group by employee_id, salary
--order by employee_id;

SELECT e.employee_id employee, count(jh.employee_id) job_switch
from employees e left outer join job_history jh on(e.employee_id = jh.employee_id)
group by e.employee_id;

SELECT  d.DEPARTMENT_name, j.job_title, count(e.employee_id)
from jobs j join departments d on (1<2) left outer join employees e on(e.job_id = j.job_id and e.department_id = d.DEPARTMENT_ID)
group by d.department_name, j.job_title;

SELECT e1.last_name, count(e2.employee_id) countofemployees
from employees e1 left outer join employees e2 on ( e1.hire_date > e2.hire_date)
group by e1.employee_id, e1.last_name;

SELECT e1.last_name, count(distinct e2.employee_id) countofemployees
from employees e1 left outer join employees e2 on ( e1.hire_date > e2.hire_date)
group by e1.employee_id, e1.last_name;

select e1.employee_id, count(distinct e2.employee_id) hired_after, count(distinct e3.employee_id) hired_before
from employees e1 left outer join employees e2 on (e1.hire_date < e2.hire_date) left outer join employees e3 on (e1.hire_date > e3.hire_date)
group by e1.employee_id;

select e1.employee_id
from employees e1 join employees e2 on (e1.employee_id <> e2.employee_id and e1.employee_id > e2.employee_id)
group by e1.employee_id
having count(e2.employee_id) >= 3;

select e1.last_name, count(distinct e2.employee_id) + 1 rank
from employees e1 left outer join employees e2 on(e1.salary < e2.salary)
group by e1.employee_id, e1.last_name
order by rank;

select e1.last_name, count(distinct e2.employee_id) + 1 rank
from employees e1 left outer join employees e2 on(e1.salary < e2.salary)
group by e1.employee_id, e1.last_name
having count(distinct e2.employee_id) + 1 <= 3
order by rank;

select e.last_name
from employees e join departments d on(d.department_name = 'Sales' and e.DEPARTMENT_ID = d.DEPARTMENT_ID);

select e.last_name
from employees e
where e.department_id = (select department_id
from departments d
where d.department_name = 'Sales');

select e1.last_name, e1.salary
from employees e1
where e1.salary > (
    select min(e2.salary)
    from employees e2
    where e2.employee_id <> e1.employee_id
);

select e1.last_name, e1.salary
from employees e1
where e1.salary > ALL (
    select e2.salary
    from employees e2
    where e2.employee_id <> e1.employee_id
);

select e1.last_name, e1.salary
from employees e1
where (e1.salary - (
    select avg(e2.salary)
    from employees e2
    where e2.employee_id <> e1.employee_id
)) between -5000 and 5000;

SELECT e1.last_name, e1.salary
from employees e1
where (select count(e2.employee_id)
    from employees e2
    where e2.salary < e1.salary
) >= 3;

SELECT (select d.department_name
from departments d
where d.department_id = e.department_id) department_names
from employees e
where department_id is not null
group by department_id
having avg(salary) > (
select min(salary)
from employees e2
);

SELECT (select d.department_name
from departments d
where d.department_id = e1.department_id) department_names
from employees e1
where e1.department_id is not null
group by e1.department_id
having count(e1.employee_id) > all (SELECT count(e2.employee_id)
from employees e2
where e2.department_id is not null and e2.department_id <> e1.DEPARTMENT_ID
group by e2.department_id);

select distinct(jh.employee_id)
from job_history jh
where (select e.department_id
        from employees e
        where e.employee_id = jh.employee_id) <> jh.department_id;

select e1.last_name, D.max_salary, D.min_salary
    from employees e1 join (select e2.DEPARTMENT_ID, min(e2.SALARY) min_salary, max(e2.salary) max_salary
    from employees e2
    group by e2.department_id
    ) D on (e1.department_id = D.department_id);

SELECT e1.last_name, (select jh2.job_title
                        from jobs jh2
                        where jh2.job_id = e1.job_id
                        ) job_titles
from employees e1
where e1.salary > all (select e2.salary
                    from employees e2
                    where e2.employee_id <> e1.employee_id and e2.job_id = e1.job_id
                    );

select distinct e1.employee_id
from employees e1
minus (
  select distinct e2.manager_id
from employees e2 
where e2.manager_id is not null
);

select e1.LAST_NAME
from (select e1.employee_id
from employees e1
minus (
  select distinct e2.manager_id
from employees e2 
where e2.manager_id is not null
)) D join employees e1 on (e1.employee_id = D.employee_id);

select l.LOCATION_ID
from locations l
minus(
    select d.location_id
    from departments d 
    where d.location_id is not null
);

select e1.department_id, count(case 
                                when salary < 5000 then employee_id
                                else null
                                end) A_grade
from employees e1
where e1.department_id is not null
group by e1.department_id;

select e1.department_id, sum(decode(floor(salary/5000),0,1,0)) A_grade
from employees e1
where e1.department_id is not null
group by e1.department_id;

select d.DEPARTMENT_NAME, (e3.first_name ||' '|| e3.last_name) full_name, e3.salary
from departments d join employees e3 on (d.manager_id = e3.employee_id) 
where (select country_id
        from locations l
        where l.location_id = d.location_id) = 'US' and d.manager_id is not null and (e3.salary between 10000 and 15000) and (select count(e2.manager_id)
                                        from employees e2
                                        where e2.manager_id is not null and e2.manager_id = d.manager_id
                                        ) >= 2
order by e3.salary desc, d.DEPARTMENT_ID asc;
                                    


















