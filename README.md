# miniRT

---

### 윈도우 규칙

- [x]  ESC키를 눌렀을 시 프로그램 종료
- [x]  X 눌렀을 시 프로그램 종료
- [x]  키보드 특정 키를 누르면 다음 카메라에서 보이는 화면을 보여주기
- [x]  해상도가 디스플레이 해상도를 넘었을 경우, 디스플레이 해상도에 맞춰서 보여주기

### .rt파일 규칙

- [x]  window/rendered image size를 포함
- [x]  각각 요소들은 빈 줄들로 구별됨
- [x]  각각 요소들의 성질들은 space로 구별됨
- [x]  대문자로 된 요소들은 한 개만 선언할 수 있음

### 구현해야될 요소들

- [x]  R (Resolution)
- [x]  A (Ambient lighting)
- [x]  c (Camera)
- [x]  l (Light)
- [x]  sp (Sphere)
- [x]  pl (Plane)
- [x]  sq (Square)
- [x]  cy (Cylinder)
- [x]  tr (Triangle)

---

# 1. 빨간 원(구) 생성

---

```c
int				hit_sphere(t_point3 center, double radius, t_ray r)
{
	t_point3	oc;
	double		a, b, c;
	double		discriminant;

	oc = v_minus(r.orig, center);
	a = v_dot(r.dir, r.dir);
	b = 2.0 * v_dot(oc, r.dir);
	c = v_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

t_point3		ray_color(t_ray r)
{
	double		t;
	t_vec3		unit;

	if (hit_sphere(vec(0, 0, -1), 0.5, r))
		return (vec(1, 0, 0));
	unit = v_unit(r.dir);
	t = 0.5 * (unit.y + 1.0);
	return(v_plus(v_mul(1.0 - t, vec(1, 1, 1))
				, v_mul(t, vec(0.5, 0.7, 1.0))));
}

int				main(void)
{
	t_screen	screen;
	int			i;
	int			j;
	int			width;
	int			height;
	t_color3	rgb;
	t_ray		r;
	t_camera	cam;

	width = 500;
	height = 300;
	screen.mlx = mlx_init();
	screen.win = mlx_new_window(screen.mlx, width, height, "test");
	screen.img = mlx_new_image(screen.mlx, width, height);
	screen.addr = mlx_get_data_addr(screen.img, &screen.bpp, &screen.size_l, &screen.endian);

	//cam setting
	cam.viewport_h = 2.0;
	cam.aspec_ratio = (double)width / height; //**중요 double로 캐스팅 해주지 않으면 int로 생각해서 1이된다.
	cam.viewport_w = cam.aspec_ratio * cam.viewport_h;
	cam.focal_len = 1.0;

	cam.origin = (t_point3){0, 0, 0};
	cam.horizontal = (t_vec3){cam.viewport_w, 0, 0};
	cam.vertical = (t_vec3){0, cam.viewport_h, 0};
	cam.left_bottom = v_minus(
						v_minus(
								v_minus(cam.origin, v_div(cam.horizontal, 2))
								, v_div(cam.vertical, 2)
								)
						, vec(0, 0, cam.focal_len)
						);

	j = height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < width)
		{
			double u = (double)i / (width - 1);
			double v = (double)j / (height - 1);
			r = ray(cam.origin,
				v_minus(v_plus(v_plus(cam.left_bottom, v_mul(u, cam.horizontal))
								, v_mul(v, cam.vertical)), cam.origin)
			);
			set_color(&screen, i, height - 1 - j, (t_color3)ray_color(r));
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(screen.mlx, screen.win, screen.img, 0, 0);
	mlx_loop(screen.mlx);
}
```

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8edac30a-d5df-4945-a0fd-c22f05f61326/_2021-06-06__5.59.25.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8edac30a-d5df-4945-a0fd-c22f05f61326/_2021-06-06__5.59.25.png)

$ray = orig + t * dir$

⇒ t값을 알면 ray의 특정 좌표를 알 수 있음.

<aside>
💡 구가 (1, 0, 0)에 있어도 화면에 보이는 문제가 있음

</aside>

<aside>
💡 음영이 없기 때문에 원처럼 보임

</aside>

# 2. 법선벡터를 통한 Shading & 근의 공식의 사용

---

- 법선벡터를 사용하는 이유?
법선벡터 = 단위길이 벡터 이므로 값이 -1 ~ 1 사이이다. → x, y, z 좌표를 r, g, b로 맵핑하기가 쉽다.

```c
float			hit_sphere(t_point3 center, double radius, t_ray r)
{
	t_point3	oc;
	double		a, b, c;
	double		discriminant;

	oc = v_minus(r.orig, center);
	a = v_dot(r.dir, r.dir);
	b = 2.0 * v_dot(oc, r.dir);
	c = v_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

t_point3		ray_color(t_ray r)
{
	double		t;
	t_vec3		unit;
	t_vec3		n;

	if ((t = hit_sphere(vec(0, 0, -1), 0.5, r)) > 0.0)
	{
		n = v_unit(v_minus(ray_at(&r, t), vec(0, 0, -1)));
		return (v_mul(0.5, vec(n.x + 1, n.y + 1, n.z + 1)));
	}
	unit = v_unit(r.dir);
	t = 0.5 * (unit.y + 1.0);
	return(v_plus(v_mul(1.0 - t, vec(1, 1, 1))
				, v_mul(t, vec(0.5, 0.7, 1.0))));
}
```

- 판별식 < 0 인 경우 -1.0 을 리턴
- 그 외의 경우 근의 공식을 유도하여 그 값을 리턴한다.
결과값이 음수일 경우 ray.dir의 반대방향에 구체가 존재하는 것이므로, 결과값이 양수인 경우에만 법선벡터를 활용하여 rgb를 정해준다.
- 법선벡터는 -1 ~ 1 범위인데 rgb는 양수이므로 1씩 더해준뒤 1/2를 곱해 0~1 범위로 변환해준다.
-1 ≤ n ≤ 1 ⇒ (1을 더함)0 ≤ n ≤ 2 ⇒ (2로 나눔) 0 ≤ n ≤ 1
- 구의 방정식

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a28ed5ea-fd02-4e66-b154-f2b8015ba66b/__-1.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a28ed5ea-fd02-4e66-b154-f2b8015ba66b/__-1.png)

$$
구의\;방정식 : (x-C_x)^2+(y-C_y)^2+(x-C_z)^2 = r^2\\
벡터화 : (P-C)\cdot(P-C) = r^2\\
광선 : P(t)=A+t\vec b\;(A:ray.orig,\;\vec b:ray.dir)\\
$$

위의 식들을 활용하여, t에 대한 방정식으로 정리한다.

$$
(P(t)-C)\cdot(P(t)-C)=r^2\\
t^2\vec b\cdot\vec b+2t\vec b\cdot(A-C)+(A-C)\cdot(A-C)-r^2=0
$$

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2194b5be-a8ce-44fc-b6b7-532005cd3a14/__.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2194b5be-a8ce-44fc-b6b7-532005cd3a14/__.png)

$$
a = r.dir \cdot r.dir\; = ||\vec{r.dir}||^2(\therefore a > 0)\\
b = 2(oc \cdot r.dir)\;(\therefore b < 0)\\
c = oc \cdot oc - radius^2\;(\therefore c > 0) \\
discriminant = b^2 - 4ac \\
if\;discriminant>0,\;then\; formula\,>0\\
(\because\sqrt{b^2-4ac}<\sqrt{b^2} = ||b||)
$$

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5f030422-f845-427e-9505-458638d4e31b/___2.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5f030422-f845-427e-9505-458638d4e31b/___2.png)

$$
if\;discriminant>0,\;then\;formula < 0\\
(\because a>0,\;b>0,\;c>0,\;\sqrt{b^2-4ac}<||b||)
$$

위의 방식으로 이전에 [0,1,0]에 존재하는 구가 보였던 문제가 해결되었다.

근의 공식(quadratic_formula)이 양수일 때에만 카메라가 보는 방향에 구가 존재하며, 음수일 경우에는 카메라의 반대방향에 구가 존재한다.

판별식(discriminant)는 양수이거나 0일 때에만 근이 존재하며, 양수일 때에는 근이 두개, 0일 때에는 근이 한개 존재한다.

# 3. 구 구조체 생성

---

```c
typedef struct	s_sphere
{
	double		radius;
	double		diameter;
	t_point3	center;
}				        t_sphere;
```

위와 같이 구 구조체를 생성한다.

```c
t_sphere	*new_sphere(t_point3 center, double diameter)
{
	t_sphere	*sp;

	if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (0);
	sp->center = center;
	sp->diameter = diameter;
	sp->radius = diameter / 2.0;
	return (sp);
}
```

구조체를 초기화 해 줄 함수를 생성한다.

# 4. 판별식 다듬기

---

$$
b_{half} = b / 2\\
$$

라고 가정했을 시,

$$
{-b\pm\sqrt{b^2-4ac}\over2a}={-2b_{half}\pm\sqrt{(2b_{half})^2-4ac}\over2a}={-b_{half}\pm\sqrt{b_{half}^2-ac}\over a}
$$

로 정리할 수 있다.

```c
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		formula;

	oc = v_minus(r->orig, sp->center);
	a = v_len2(r->dir);
	half_b = v_dot(oc, r->dir);
	c = v_len2(oc) - sp->radius * sp->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (INFINITY);
```

v_dot(r→dir, r→dir) 와 같은 경우는 같은 변수를 두 개 복사해서 보내기 때문에 효율적인 메모리 사용을 위해 v_len2(r→dir)을 사용하였다.

$$
{\vec A\cdot\vec A = ||\vec A||^2}
$$

# 5. 광선과 object가 부딪혔을 때

---

광선하나에 object가 여러개 부딪힌다고 가정해보자.

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2e858a6c-8774-4f58-8036-88b6c9d59e23/__-1_2.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2e858a6c-8774-4f58-8036-88b6c9d59e23/__-1_2.png)

그림과 같이 t_max보다 멀리 있는 점은 보이지 않게 된다.
따라서 object에 광선이 부딪혔을 때마다 t_max와 t값을 비교를 해 더 작은 값을 t_max로 바꿔주고, t_max 값이 변경되었을 때마다, t_rec이라는 구조체에 정보를 덮어씌워준다.
모든 object들을 점검하고 난 후에는 t_rec 구조체에 저장되어 있는 정보들은 우리의 화면에 보여지는 정보들이 된다.

```c
typedef struct	s_rec
{
	t_point3	p;
	double		t;
	t_vec3		n;
	double		t_max;
	double		t_min;
	int			front_face;
}				        t_rec;
```

```c
float			hit_sphere(t_sphere *sp, t_ray *r, t_rec *rec)
{
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		formula;

	oc = v_minus(r->orig, sp->center);
	a = v_len2(r->dir);
	half_b = v_dot(oc, r->dir);
	c = v_len2(oc) - sp->radius * sp->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (INFINITY);
	formula = (-half_b - sqrt(discriminant)) / a;
	if (formula < rec->t_min || formula >= rec->t_max)
	{
		formula = (-half_b + sqrt(discriminant)) / a;
		if (formula < rec->t_min || formula >= rec->t_max)
			return (INFINITY);
	}
	rec->t = formula;
	rec->p = ray_at(r, formula);
	rec->n = v_div(v_minus(rec->p, sp->center), sp->radius);
	set_face_normal(r, rec);
	return (1);
}
```

### set_normal_face에 관하여

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/bcf4b94e-ab30-4c62-9da8-cacba0799aec/__-1_3.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/bcf4b94e-ab30-4c62-9da8-cacba0799aec/__-1_3.png)

그림과 같이 카메라가 구 안에 있는 경우 벡터 ray.dir와 벡터 n의 내적의 값이 양수가 된다.
object 와 광선 간의 상호작용을 계산하기 위해서는 법선과 광선이 반대방향을 향하고 있어야한다.
때문에 set_normal_face()라는 함수를 통해 n의 방향을 바꿔준다.

```c
void			set_face_normal(t_ray *r, t_rec *rec)
{
	rec->front_face = v_dot(r->dir, rec->n) < 0;
	rec->n = rec->front_face ? rec->n : v_mul(-1, rec->n);
}
```

### formula를 두 번 계산하는 이유?

어차피 가까운 point를 t_max로 잡을 거면, 굳이 두 formula값을 다 확인할 필요는 없다.
하지만 위에서 말했던 것과 같이 카메라가 object안에 있는 경우에는 두 값을 다 확인해야 카메라가 어느 곳을 보고 있는지 알 수 있기 때문에 formula를 두 번 계산한다.

# 6. object가 여러개인 경우

---

object가 구에만 한정되어 있지도 않고, 단 한개에만 한정되어 있는 것도 아니기 때문에, 여러개의 object를 담기 위해서 t_object라는 구조체를 생성해야 한다.

```c
typedef struct	s_object
{
	int			type;
	void		*element;
	void		*next;
}				        t_object;
```

```c
t_object	*new_object(int type, void *element)
{
	t_object	*obj;

	if (!(obj = (t_object *)malloc(sizeof(t_object))))
		return (0);
	obj->type = type;
	obj->element = element;
	obj->next = NULL;
	return (obj);
}

void			add_object(t_object **list, t_object *new)
{
	t_object	*tmp;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
```

위와 같이 add_object함수를 통하여 리스트 뒤에 차곡차곡 object들을 쌓을 수 있도록 만든다.

```c
int				hit_sphere(t_sphere *sp, t_ray *r, t_rec *rec)
{
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		formula;

	oc = v_minus(r->orig, sp->center);
	a = v_len2(r->dir);
	half_b = v_dot(oc, r->dir);
	c = v_len2(oc) - sp->radius * sp->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	formula = (-half_b - sqrt(discriminant)) / a;
	if (formula < rec->t_min || formula >= rec->t_max)
	{
		formula = (-half_b + sqrt(discriminant)) / a;
		if (formula < rec->t_min || formula >= rec->t_max)
			return (0);
	}
	rec->t = formula;
	rec->p = ray_at(r, formula);
	rec->n = v_div(v_minus(rec->p, sp->center), sp->radius);
	set_face_normal(r, rec);
	return (1);
}

int				hit_obj(t_object *obj, t_ray *r, t_rec *rec)
{
	int			rst;

	rst = 0;
	if (obj->type == SPHERE)
		rst = hit_sphere((t_sphere *)obj->element, r, rec);
	return (rst);
}

int				hit(t_object *obj, t_ray *r, t_rec *rec)
{
	int			hit_anything;
	t_rec		tmp_rec;

	tmp_rec = *rec; //rec.t_max 와 rec.t_min을 대입해 초기화
	hit_anything = 0;
	while(obj)
	{
		if (hit_obj(obj, r, &tmp_rec))
		{
			hit_anything = 1;
			tmp_rec.t_max = tmp_rec.t;
			*rec = tmp_rec;
		}
		obj = obj->next;
	}
	return (hit_anything);
}
```

1. hit()에서 while문을 통해 object들을 하나씩 확인하면서 제일 카메라와 가까이 존재하는 object를 탐색한다.
2. hit_obj()를 통해 추후에 sphere뿐 아니라 다른 object들도 적용할 것이다.

```c
  t_object   *obj;

	obj = NULL;
	add_object(&obj, new_object(SPHERE, new_sphere(vec(-2, 0, -5), 4)));
	add_object(&obj, new_object(SPHERE, new_sphere(vec(2, 0, -5), 4)));
	add_object(&obj, new_object(SPHERE, new_sphere(vec(0, -1000, -3), 990*2)));
```

위와 같이 main에서 obj를 테스트 해보고 싶은 만큼 생성한다.

```c
set_color(&screen, i, height - 1 - j, (t_color3)ray_color(&r, obj));
```

set_color()를 obj를 넘겨주는 방식으로 바꾼다.

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8906ec2d-0793-4b97-95d9-1a5238b3820e/_2021-06-07__8.33.20.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8906ec2d-0793-4b97-95d9-1a5238b3820e/_2021-06-07__8.33.20.png)

# 7. Phong lighting

---

먼저 빛 구조체와 초기화 함수를 정의해준다.

```c
typedef struct	s_light
{
	t_point3	orig;
	t_color3	color;
	double		bright_ratio;
}				        t_light;
```

```c
t_light		*new_light(t_point3 orig, t_color3 color, double ratio)
{
	t_light		*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return (0);
	light->orig = orig;
	light->color = color;
	light->bright_ratio = ratio;
	return (light);
}
```

구와 t_rec에도 색상을 추가해준다.

```c
typedef struct	s_sphere
{
	double		radius;
	double		diameter;
	t_point3	center;
	t_color3	albedo;
}				        t_sphere;

typedef struct	s_rec
{
	t_point3	p;
	double		t;
	t_vec3		n;
	double		t_max;
	double		t_min;
	int			front_face;
	t_color3	albedo;
}				        t_rec;
```

```c
t_sphere	*new_sphere(t_point3 center, double diameter, t_color3 albedo)
{
	t_sphere	*sp;

	if (!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (0);
	sp->center = center;
	sp->diameter = diameter;
	sp->radius = diameter / 2.0;
	sp->albedo = albedo;
	return (sp);
}
```

hit_sphere() 함수에서 rec에 정보들을 저장하는 부분에도 색상을 추가해준다.

```c
rec->albedo = sp->albedo;
```

sphere 구조체를 수정해줬으니 main의 object를 추가하는 부분도 수정해주고, 빛 object도 추가해준다.

```c
  //obj
	obj = NULL;
	add_object(&obj, new_object(SPHERE, new_sphere(point(-2, 0, -5), 4, color(0.5, 0, 0))));
	add_object(&obj, new_object(SPHERE, new_sphere(point(2, 0, -5), 4, color(0, 0.5, 0))));
	add_object(&obj, new_object(SPHERE, new_sphere(point(0, -1000, -3), 990*2, color(1, 1, 1))));

	//light
  t_object   *lights;
	lights = NULL;
	add_object(&lights, new_object(LIGHT, new_light(point(0, 5, 0), color(1, 1, 1), 0.5)));
```

screen 구조체에 object 와 light를 추가한 뒤 위에서 만든 objects를 넘겨준다.

```c
  screen.object = obj;
	screen.light = lights;
	double		ka;
	ka = 0.1;
	screen.ambient = v_mul(ka, color(1, 1, 1));
```

object에 도달한 빛은

$$
Ambient + \sum(Diffuse + Specular)
$$

로 표현된다.

ray_color()함수에 t_ray뿐만 아니라 t_screen도 같이 보내주어서, 빛의 정보들을 사용할 수 있게 만든다.

```c
t_color3		ray_color(t_screen *screen, t_ray *r)
{
	double		t;
	t_vec3		unit;
	t_rec		rec;

	rec.t_min = EPSILON;
	rec.t_max = INFINITY;
	if (hit(screen->object, r, &rec))
		return (phong_lighting(screen, &rec, r));
	unit = v_unit(r->dir);
	t = 0.5 * (unit.y + 1.0);
	return(v_plus(v_mul(1.0 - t, vec(1, 1, 1))
				, v_mul(t, vec(0.5, 0.7, 1.0))));
}
```

hit가 되면, phong_lighting이라는 함수로 가서 색을 계산하도록 한다.

```c
t_color3		get_point_light(t_ray *r, t_light *light, t_rec *rec)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		kd;

	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
	double		ksn;
	double		ks;

	double		brightness;

	light_dir = v_unit(v_minus(light->orig, rec->p));
	kd = fmax(v_dot(rec->n, light_dir), 0.0);
	diffuse = v_mul(kd, light->color);

	view_dir = v_unit(v_mul(-1, r->dir));
	reflect_dir = reflect(v_mul(-1, light_dir), rec->n);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(v_dot(view_dir, reflect_dir), 0.0), ksn);
	specular = v_mul(spec, v_mul(ks, light->color));

	brightness = light->bright_ratio * LUMEN;

	return (v_mul(brightness, v_plus(specular, diffuse)));
}

t_color3		phong_lighting(t_screen *screen, t_rec *rec, t_ray *r)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color(0, 0, 0);
	lights = screen->light;
	while (lights)
	{
		light_color = v_plus(light_color, get_point_light(r, lights->element, rec));
		lights = lights->next;
	}
	light_color = v_plus(light_color, screen->ambient);
	return (v_min(v_mul2(light_color, rec->albedo), color(1, 1, 1)));
}
```

get_point_light() 함수에서는 diffuse+specular 를 반환한다.

### DIFFUSE

물체는 빛과 법선이 일치할 수록 밝아지고, 그 각이 벌어질 수록 어두워진다. 이를 이용하여 diffuse를 나타낸다.

빛(표면→빛)벡터와 법선벡터를 내적했을 시 음수가 나올경우(90도 ~ 270도) 0으로 만들어 빛이 닿지 않은 것처럼 계산한다.

$$
\vec A\cdot \vec B = ||A||*||B||*cos\theta\\
$$

벡터의 내적은 위와 같이 하며, 벡터A 와 벡터 B가 단위벡터일 경우 내적의 값은 cosθ만 남는다. cosθ는 빛벡터와 법선벡터가 0~90도일 때 1~0이므로 이를 diffuse의 강도 계수인 kd로 이용한다.

![출처 : [https://ally10.tistory.com/23](https://ally10.tistory.com/23)](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/238016bb-5dcc-4b2c-9cfe-4956c362f1ec/Untitled.png)

출처 : [https://ally10.tistory.com/23](https://ally10.tistory.com/23)

### SPECULAR

물체의 반짝이는 하이라이팅을 표현한다.

카메라(교점→카메라)벡터와 법선벡터를 기준으로 빛벡터를 대칭시킨 빛대칭벡터 사이각의 크기에 따른 코사인 값을 spec으로 사용하며, 물체의 반짝거리는 정도인 shiniess value를 ksn변수, 0~1 사이의 임의의 값으로 설정하는 specular 강도를 ks변수라고 한다.

카메라벡터와 빛대칭벡터가 일치할 때 카메라에 도달한 빛의 양이 가장 많을 것이고, 사이각이 커질 수록 빛의 양은 줄어든다.

diffuse와 마찬가지로 둘 사이의 각 cosθ를 spec으로 이용한다.

![출처 : [https://ally10.tistory.com/23](https://ally10.tistory.com/23)](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/543676f5-e6fc-4559-9ab4-72a621b164e2/Untitled.png)

출처 : [https://ally10.tistory.com/23](https://ally10.tistory.com/23)

# 8. 그림자

---

스크린에 object들이 보이게끔 하는 과정에서는 카메라에서 출발한 광선을 이용해 object에 부딪히는지의 여부를 이용하였다.

그림자가 생기게 하는 과정에서는 이와 비슷하게 hit한 부분(p)에서 출발해 빛을 향해 광선을 쏘아 그 사이에 물체가 있는지 판별한다.

(그림)

 

```c
int				in_shadow(t_object *objs, t_ray *light_r, double light_len)
{
	t_rec		rec;

	rec.t_min = 0
	//rec.t_max = light_len;
	rec.t_max = 1;
	if (hit(objs, light_r, &rec))
		return (1);
	return (0);
}
```

```c
  light_dir = v_minus(light->orig, rec->p);
	light_len = v_len(light_dir);
	light_ray = ray(v_plus(rec->p, v_mul(EPSILON, rec->n)), light_dir);
	if (in_shadow(screen->object, &light_ray, light_len))
		return (color(0, 0, 0));
	light_dir = v_unit(light_dir);
	kd = fmax(v_dot(rec->n, light_dir), 0.0);
	diffuse = v_mul(kd, light->color);
```

get_point_light() 에서 단위벡터였던 light_dir을 그냥 접점 p에서 빛의 원점 orig로 향하는 벡터로 바꿔준 후, 필요한 값들을 in_shadow()함수로 보낸다.

후에 light_dir을 다시 단위벡터로 변경해준다.

(주의) rec.t_max = light_len으로 해줬더니 평면을 제작할 때 그림자가 생기지 말아야 할 부분에서 그림자가 생기는 오류가 발생하였다. light_r의 dir이 카메라 광선과의 접점→빛의 원점 벡터이며, 그 사이에 존재하는 object를 탐색하는 것이기 때문에 t_max를 1로 두어야한다. t가 1이라면 광선의 hit point는 빛의 원점이 될 것이다.(그 이상으로 커지면 빛의 뒷부분을 hit하게 된다.)

# 9. 안티에일리어싱

---

![안티에일리어싱 적용 전](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/985bdbd7-1af8-45e8-850b-197201f7842b/_2021-06-09__8.56.50.png)

안티에일리어싱 적용 전

![안티에일리어싱 적용 후](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/53c6109e-50dd-41d8-8c44-ab2fd03adb04/_2021-06-09__8.57.54.png)

안티에일리어싱 적용 후

적용 전과 적용 후의 사진을 비교해보면 적용 후가 조금 더 부드러운 것을 알 수 있다.

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5f0b5e86-5b04-479a-b575-4cf5ee06e321/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5f0b5e86-5b04-479a-b575-4cf5ee06e321/Untitled.png)

좌측은 안티에일리어싱 적용 전이고, 우측은 적용 후의 모습이다. 적용전에는 픽셀마다 색이 고정되어 있는 느낌이라면, 우측은 색이 조금 더 자유로운 느낌이다.

```c
j = height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < width)
		{
			k = 0;
			color_tmp = color(0, 0, 0);
			while (k < SAMPLE_PER_PIXEL)
			{
				double u = ((double)i + random_float(1)) / (width - 1);
				double v = ((double)j + random_float(1)) / (height - 1);
				r = ray(cam.origin,
						v_minus(v_plus(v_plus(cam.left_bottom, v_mul(u, cam.horizontal))
									, v_mul(v, cam.vertical)), cam.origin)
					);
				color_tmp = v_plus(color_tmp, ray_color(&screen, &r));
				k++;
			}
			set_color(&screen, i, height - 1 - j, v_div(color_tmp, SAMPLE_PER_PIXEL));
			i++;
		}
		j--;
	}
```

안티 에일리어싱을 적용하기 위해 SAMPLE_PER_PIXEL이라는 값을 define해준다. (나는 여기서 100으로 정해주었다.)

그러면 k가 증가하면서 SAMPLE_PER_PIXEL만큼 한 픽셀에서 코드를 더 반복하게 되는데, 이 때 random_float()라는 함수를 이용해 u가 i < u < i+1 사이에서 값이 자유자재로 변하게 만들어준다. (v도 마찬가지)

이렇게 구한 색들을 color_tmp라는 변수에 다 더해준 뒤, while k문을 탈출할 때 더해진 색들을 SAMPLE_PER_PIXEL로 나누어 평균값을 구해준다.

# 10. 자유자재 카메라

---

기존에는 카메라를 [0, 0, 0]에 고정했다면, 지금은 조금 더 자유롭게 카메라를 위치시키고 싶다.

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2ee51a5e-ab4f-4dd2-90e8-e9ea4e8628bc/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2ee51a5e-ab4f-4dd2-90e8-e9ea4e8628bc/Untitled.png)

우리는 위 사진에서 lookfrom, lookat, vup을 알고 있기 때문에 v, u, w를 구할 수 있다. (vup은 lookat이 y좌표가 0이 아니고, x, z좌표가 0일 때를 제외하고 [0, 1, 0]으로 고정해 줄 것이다. 반대의 경우에는 [0, 0, -1]로 고정해 줄 것이다.)

$$
\vec w = -1 \times \vec{lookat}\\
\vec u = \vec{vup} \times \vec{w}\\
\vec v = \vec{w} \times \vec{u}
$$

```c
  double	theta;
	double	h;
	t_vec3	u, v, w;

	theta = degrees_to_radians(90);
	h = tan(theta / 2);
	cam.aspec_ratio = (double)width / height;
	cam.viewport_h = 2 * h;
	cam.viewport_w = cam.aspec_ratio * cam.viewport_h;
	cam.origin = point(0, 5, -5);
	cam.lookat = vec(0, -1, 0);
	w = v_unit(v_mul(-1, cam.lookat));
	if (cam.lookat.x == 0 && cam.lookat.y != 0 && cam.lookat.z == 0)
		cam.vup = vec(0, 0, -1);
	else
		cam.vup = vec(0, 1, 0);
	u = v_unit(v_cross(cam.vup, w));
	v = v_cross(w, u);
	cam.horizontal = v_mul(cam.viewport_w, u);
	cam.vertical = v_mul(cam.viewport_h, v);
	cam.left_bottom = v_minus(
						v_minus(
							v_minus(cam.origin, v_div(cam.horizontal, 2))
							, v_div(cam.vertical, 2))
						, w
					);
```

원래 lookat은 바라보고 있는 곳의 좌표로 사용되지만, 내가 작성할 코드에서는 lookat을 바라보고 있는 방향벡터로 받아올 것이기 때문에 w벡터 자체를 lookat 벡터의 반대방향으로 잡아주었다.

# 11. EPSILON

---

epsilon은 셀프 섀도잉을 피하기 위해 존재한다. 반사레이가 반사된 표면과 즉시 교차하기 때문에 표면 그림자를 그리게 되고, 이를 피하기 위해 반사된 광선은 반사된 지점에서 정확하게 시작되는게 아니라 표면으로부터 약간 떨어져서 시작한다. epsilon은 이 거리를 지정하고 있으며, m단위이다.

기본값으로 0.0001 을 사용한다.

```c
# define EPSILON 1e-4
```

- 그림자를 생성하기 위한 ray를 지정할 때

```c
light_ray = ray(v_plus(rec->p, v_mul(EPSILON, rec->n)), light_dir);
```

- 화면에 object를 띄우기 위해 hit()함수를 사용할 때
