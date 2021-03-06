// Object.i,v 1.31 2001/08/21 19:00:22 parsons Exp

// ****************************************************************

ACE_INLINE
CORBA_Object::CORBA_Object (int)
  : is_collocated_ (0),
    servant_ (0),
    is_local_ (1),
    proxy_broker_ (0),
    protocol_proxy_ (0),
    refcount_ (1),
    refcount_lock_ ()
{
}

ACE_INLINE CORBA::ULong
CORBA_Object::_incr_refcnt (void)
{
  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, guard, this->refcount_lock_, 0);
  return this->refcount_++;
}

ACE_INLINE CORBA::ULong
CORBA_Object::_decr_refcnt (void)
{
  {
    ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, mon, this->refcount_lock_, 0);
    this->refcount_--;
    if (this->refcount_ != 0)
      return this->refcount_;
  }

  delete this;
  return 0;
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object::_duplicate (CORBA_Object_ptr obj)
{
  if (obj)
    obj->_add_ref ();
  return obj;
}

// ************************************************************
// These are in CORBA namespace

ACE_INLINE void
CORBA::release (CORBA_Object_ptr obj)
{
  if (obj)
    obj->_remove_ref ();
}

ACE_INLINE CORBA::Boolean
CORBA::is_nil (CORBA_Object_ptr obj)
{
  if (obj == 0)
    {
      return 1;
    }

  return CORBA_Object::is_nil_i (obj);
}

// ************************************************************

// Null pointers represent nil objects.

ACE_INLINE CORBA_Object_ptr
CORBA_Object::_nil (void)
{
  return 0;
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object::_unchecked_narrow (CORBA_Object_ptr obj, CORBA::Environment &)
{
  if (CORBA::is_nil (obj))
    return CORBA::Object::_nil ();

  if (obj->is_local_)
    return
      ACE_reinterpret_cast (CORBA::Object_ptr,
                            obj->_tao_QueryInterface
                            (ACE_reinterpret_cast (ptr_arith_t,
                                                   &CORBA::Object::_tao_class_id)));
  else
    return CORBA::Object::_duplicate (obj);
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object::_narrow (CORBA_Object_ptr obj, CORBA::Environment &ACE_TRY_ENV)
{
  return CORBA_Object::_unchecked_narrow (obj, ACE_TRY_ENV);
}

ACE_INLINE TAO_Stub *
CORBA_Object::_stubobj (void) const
{
  return this->protocol_proxy_;
}

// *************************************************************
// Inline operations for class CORBA_Object_var
// *************************************************************

ACE_INLINE
CORBA_Object_var::CORBA_Object_var (void)
  : ptr_ (CORBA_Object::_nil ())
{
}

ACE_INLINE
CORBA_Object_var::CORBA_Object_var (CORBA_Object_ptr p)
  : ptr_ (p)
{}

ACE_INLINE
CORBA_Object_var::~CORBA_Object_var (void)
{
  CORBA::release (this->ptr_);
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_var::ptr (void) const
{
  return this->ptr_;
}

ACE_INLINE
CORBA_Object_var::CORBA_Object_var (const CORBA_Object_var &p) // copy constructor
        : ptr_ (CORBA_Object::_duplicate (p.ptr ()))
{}

ACE_INLINE CORBA_Object_var &
CORBA_Object_var::operator= (CORBA_Object_ptr p)
{
  CORBA::release (this->ptr_);
  this->ptr_ = p;
  return *this;
}

ACE_INLINE CORBA_Object_var &
CORBA_Object_var::operator= (const CORBA_Object_var &p)
{
  if (this != &p)
  {
    CORBA::release (this->ptr_);
    this->ptr_ = CORBA_Object::_duplicate (p.ptr ());
  }
  return *this;
}

ACE_INLINE
CORBA_Object_var::operator const CORBA_Object_ptr &() const // cast
{
  return this->ptr_;
}

ACE_INLINE
CORBA_Object_var::operator CORBA_Object_ptr &() // cast
{
  return this->ptr_;
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_var::operator-> (void) const
{
  return this->ptr_;
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_var::in (void) const
{
  return this->ptr_;
}

ACE_INLINE CORBA_Object_ptr &
CORBA_Object_var::inout (void)
{
  return this->ptr_;
}

ACE_INLINE CORBA_Object_ptr &
CORBA_Object_var::out (void)
{
  CORBA::release (this->ptr_);
  this->ptr_ = CORBA_Object::_nil ();
  return this->ptr_;
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_var::_retn (void)
{
  // yield ownership of managed obj reference
  CORBA_Object_ptr val = this->ptr_;
  this->ptr_ = CORBA_Object::_nil ();
  return val;
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_var::tao_duplicate (CORBA_Object_ptr p)
{
  return CORBA_Object::_duplicate (p);
}

ACE_INLINE void
CORBA_Object_var::tao_release (CORBA_Object_ptr p)
{
  CORBA::release (p);
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_var::tao_nil (void)
{
  return CORBA_Object::_nil ();
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_var::tao_narrow (
    CORBA::Object *p,
    CORBA::Environment &
  )
{
  return CORBA_Object::_duplicate (p);
}

ACE_INLINE CORBA::Object *
CORBA_Object_var::tao_upcast (void *src)
{
  CORBA_Object **tmp =
    ACE_static_cast (CORBA_Object **, src);
  return *tmp;
}

// *************************************************************
// Inline operations for class CORBA_Object_out
// *************************************************************

ACE_INLINE
CORBA_Object_out::CORBA_Object_out (CORBA_Object_ptr &p)
        : ptr_ (p)
{
  this->ptr_ = CORBA_Object::_nil ();
}

ACE_INLINE
CORBA_Object_out::CORBA_Object_out (CORBA_Object_var &p) // constructor from _var
        : ptr_ (p.out ())
{
  CORBA::release (this->ptr_);
  this->ptr_ = CORBA_Object::_nil ();
}

ACE_INLINE
CORBA_Object_out::CORBA_Object_out (const CORBA_Object_out &p) // copy constructor
        : ptr_ (p.ptr_)
{}

ACE_INLINE CORBA_Object_out &
CORBA_Object_out::operator= (const CORBA_Object_out &p)
{
  this->ptr_ = p.ptr_;
  return *this;
}

ACE_INLINE CORBA_Object_out &
CORBA_Object_out::operator= (const CORBA_Object_var &p)
{
  this->ptr_ = CORBA_Object::_duplicate (p.ptr ());
  return *this;
}

ACE_INLINE CORBA_Object_out &
CORBA_Object_out::operator= (CORBA_Object_ptr p)
{
  this->ptr_ = p;
  return *this;
}

ACE_INLINE
CORBA_Object_out::operator CORBA_Object_ptr &() // cast
{
  return this->ptr_;
}

ACE_INLINE CORBA_Object_ptr &
CORBA_Object_out::ptr (void) // ptr
{
  return this->ptr_;
}

ACE_INLINE CORBA_Object_ptr
CORBA_Object_out::operator-> (void)
{
  return this->ptr_;
}
