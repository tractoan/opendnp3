package com.automatak.dnp3.codegen

import java.lang.reflect.{Constructor, Method}

object Features extends Enumeration {
  val Fields, Methods, Constructors = Value
}

trait MethodFilter {
  def matches(method: Method) : Boolean
}

object MethodFilter {

  def acceptsAny = new MethodFilter {
    override def matches(method: Method): Boolean = true
  }

  def strictlyEqual(string: String, args: Option[Int] = None) = new MethodFilter {
    override def matches(method: Method): Boolean = {
      method.getName == string && args.map(_ == method.getParameterCount).getOrElse(true)
    }
  }
}

trait ConstructorFilter {
  def matches(c: Constructor[_]) : Boolean
}

object ConstructorFilter {

  def acceptsAny = new ConstructorFilter {
    override def matches(c: Constructor[_]): Boolean = true
  }

  def withParamTypes(params : List[String]) = new ConstructorFilter {
    override def matches(c: Constructor[_]): Boolean = {
      c.getParameters.map(p => p.getType.getName).toList == params
    }
  }
}

case class ClassConfig(clazz: Class[_], features : Set[Features.Value], mfilter: MethodFilter = MethodFilter.acceptsAny, cfilter: ConstructorFilter = ConstructorFilter.acceptsAny) {

  def isEnabled(f : Features.Value) : Boolean  = features.contains(f)

  def ifEnabled(f : Features.Value)(inner: => Iterator[String]) : Iterator[String] = {
    if(!isEnabled(f)) Iterator.empty else {
      inner
    }
  }

  def methods : Array[Method] = clazz.getDeclaredMethods.filter(mfilter.matches)

  def constructors : Array[Constructor[_]] = clazz.getConstructors.filter(cfilter.matches)
}

